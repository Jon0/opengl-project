/*
 * Animation.cpp
 *
 *  Created on: 30/08/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <math.h>
#include "Animation.h"

namespace std {

Animation::Animation(Skeleton *s) {
	numBones = s->getNumBones();
	addFrame();
}

Animation::Animation( int numPoses, pose **states, Skeleton *s) {
	numBones = s->getNumBones();
	for (int i = 0; i < numPoses; ++i) {
		v_pose.push_back( *states[i] );
	}
}

Animation::~Animation() {}

void Animation::update(float time, pose *current) {

	// set correct pose base on keyframes
	float animate_frame = fmod( time, v_pose.size() ) ;
	pose *a = &v_pose.at( (int) animate_frame );
	pose *b = &v_pose.at( ((int) animate_frame + 1) % v_pose.size() );
	float t = fmod(animate_frame, 1.0);

	//current.position = getPoint(animate_frame);;
	for (int i = 0; i < numBones; ++i) {
		current->data()[i] = slerp(a->data()[i], b->data()[i], t);
	}
}

void Animation::addFrame() {
	pose newPose;
	if (v_pose.size() > 0) {
		copyState( numBones, (pose *)&v_pose.back(), &newPose);
	}
	else {
		makeState(numBones, &newPose);
	}
	v_pose.push_back( newPose );
}

void Animation::insertFrame(float time) {
	pose newPose;
	makeState( numBones, &newPose );

	// insert at current position
	float animate_frame = fmod( time, v_pose.size() ) ;
	pose *a = &v_pose.at( (int) animate_frame );
	pose *b = &v_pose.at( ((int) animate_frame + 1) % v_pose.size() );
	float t = fmod(animate_frame, 1.0);

	for (int i = 0; i < numBones; ++i) {
		newPose.data()[i] = slerp(a->data()[i], b->data()[i], t);
	}


	//v_pose.insert()
}

void Animation::rollSelection(int id, float f) {
	if ( id < 0 ) {
		return;
	}
	// TODO: something
}

void Animation::modSelection(int frame_index, int id, float x, float y, float z) {
	Quaternion q = *fromEular(x, y, z);
	modSelection( frame_index, id, q );
}

void Animation::modSelection(int frame_index, int id, Quaternion &q) {
	if ( id < 0 ) {
		return;
	}

	pose *p = &v_pose.at(frame_index);
	p->data()[id].rotate( q );

	// quaternion to eular angle, ensure bone is within limits

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

} /* namespace std */
