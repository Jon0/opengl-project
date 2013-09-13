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
	show_animate = false;
	animate_frame = 0.0;
	frame_rate = 1.0;
	makeState(numBones, &current);
	addFrame();
}

Animation::Animation( int numPoses, pose **states, Skeleton *s) {
	numBones = s->getNumBones();
	show_animate = false;
	animate_frame = 0.0;
	frame_rate = 1.0;
	makeState(numBones, &current);
	for (int i = 0; i < numPoses; ++i) {
		v_pose.push_back( *states[i] );
	}
}

Animation::~Animation() {}

void Animation::update(float time, pose *current) {

	// set correct pose base on keyframes
	float animate_frame = fmod( time, v_pose.size() );
	pose *a = &v_pose.at( (int) animate_frame );
	pose *b = &v_pose.at( ((int) animate_frame + 1) % v_pose.size() );
	float t = fmod(animate_frame, 1.0);

	//current.position = getPoint(animate_frame);;
	for (int i = 0; i < numBones; ++i) {
		current->angle[i] = slerp(a->angle[i], b->angle[i], t);
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

void Animation::insertFrame() {
	pose newPose;
	makeState( numBones, &newPose );

	// insert at current position
	animate_frame = fmod( animate_frame + frame_rate, v_pose.size() );
	pose *a = &v_pose.at( (int) animate_frame );
	pose *b = &v_pose.at( ((int) animate_frame + 1) % v_pose.size() );
	float t = fmod(animate_frame, 1.0);

	newPose.position = a->position;	// this should use some interpolation
	for (int i = 0; i < numBones; ++i) {
		newPose.angle[i] = slerp(a->angle[i], b->angle[i], t);
	}


	//v_pose.insert()
}

void Animation::setFrame(int i) {
	animate(false);
	animate_frame = i;
}

int Animation::getFrame() {
	return animate_frame;
}

void Animation::setPlaySpeed(int s) {
	frame_rate = s;
}

void Animation::animate(bool a) {
	show_animate = a;
}

void Animation::rollSelection(int id, float f) {
	if ( id < 0 ) {
		return;
	}
	// TODO: something
}

void Animation::modSelection(int id, float x, float y, float z) {
	Quaternion q = *fromEular(x, y, z);
	modSelection( id, q );
}

void Animation::modSelection(int id, Quaternion &q) {
	if ( id < 0 ) {
		return;
	}

	pose *p = &v_pose.at(animate_frame);
	p->angle[id].rotate( q );

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
