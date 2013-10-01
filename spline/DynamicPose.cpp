/*
 * Animation.cpp
 *
 *  Created on: 30/08/2013
 *      Author: remnanjona
 */

#include <math.h>
#include "DynamicPose.h"

namespace std {

DynamicPose::DynamicPose(shared_ptr<Skeleton> s) {
	path_length = 1.0;
	numBones = s->getNumBones();
	addFrame();
}

DynamicPose::DynamicPose( int numPoses, pose **states, shared_ptr<Skeleton> s) {
	path_length = 1.0;
	numBones = s->getNumBones();
	for (int i = 0; i < numPoses; ++i) {
		v_pose.push_back( *states[i] );
	}
}

DynamicPose::~DynamicPose() {}

void DynamicPose::update(float position, pose *current) {
	/*
	 *	set correct pose base on keyframes
	 *	position is units traveled along some arc
	 */
	float time = (position * v_pose.size()) / path_length;
	float animate_frame = fmod( time, v_pose.size() ) ;
	pose *a = &v_pose.at( (int) animate_frame );
	pose *b = &v_pose.at( ((int) animate_frame + 1) % v_pose.size() );
	float t = fmod(animate_frame, 1.0);

	/*
	 *	set values on given pose
	 */
	current->adjust = a->adjust * (1 - t) + b->adjust * t;
	for (int i = 0; i < numBones; ++i) {
		current->q.data()[i] = glm::slerp(a->q.data()[i], b->q.data()[i], t);
	}
}

void DynamicPose::addFrame() {
	pose newPose;
	if (v_pose.size() > 0) {
		copyState( numBones, (pose *)&v_pose.back(), &newPose);
	}
	else {
		makeState(numBones, &newPose);
	}
	v_pose.push_back( newPose );
}

void DynamicPose::addFrame( pose newPose ) {
	v_pose.push_back( newPose );
}

void DynamicPose::insertFrame(float time) {
	pose newPose;
	makeState( numBones, &newPose );
	// TODO: repeated code....
	// insert at current position
	float animate_frame = fmod( time, v_pose.size() ) ;
	pose *a = &v_pose.at( (int) animate_frame );
	pose *b = &v_pose.at( ((int) animate_frame + 1) % v_pose.size() );
	float t = fmod(animate_frame, 1.0);

	for (int i = 0; i < numBones; ++i) {
		newPose.q.data()[i] = glm::slerp(a->q.data()[i], b->q.data()[i], t);
	}
	//v_pose.insert()
}

void DynamicPose::rollSelection(int id, float f) {
	if ( id < 0 ) {
		return;
	}
	// TODO: something
}

void DynamicPose::modSelection(int frame_index, int id, float x, float y, float z) {
	glm::quat q = glm::quat( glm::vec3(x, y, z) );
	modSelection( frame_index, id, q );
}

void DynamicPose::modSelection(int frame_index, int id, const glm::quat &q) {
	if ( id < 0 ) {
		return;
	}
	glm::quat &p = v_pose[frame_index % v_pose.size()].q[id];
	p = q * p;

	// TODO ensure bone is within limits?
	//DOF dof = skeleton->getDof(id);
	//if ((dof & DOF_RX) == DOF_RX) {
	//	drawnState->part[id]->degree[0] += x;
	//}
	//if ((dof & DOF_RY) == DOF_RY) {
	//	drawnState->part[id]->degree[1] += y;
	//}
	//if ((dof & DOF_RZ) == DOF_RZ) {
	//	drawnState->part[id]->degree[2] += z;
	//}
}

void DynamicPose::setPathLength(float l) {
	path_length = l;
}

int DynamicPose::numFrames() {
	return v_pose.size();
}

} /* namespace std */
