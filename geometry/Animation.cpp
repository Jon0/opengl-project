/*
 * Animation.cpp
 *
 *  Created on: 30/08/2013
 *      Author: remnanjona
 */

#include <math.h>
#include "Animation.h"

namespace std {

Animation::Animation(Skeleton *s) {
	skeleton = s;
	show_animate = false;
	animate_frame = 0.0;
	frame_rate = 0.01;

	addState();
}

Animation::~Animation() {
	// TODO Auto-generated destructor stub
}

pose *Animation::currentPose() {
	return &current;
}

Vec3D *Animation::getCentre() {
	return current.position;
}

void Animation::update(float time) {
	if (show_animate && v_pose.size() > 0) {
		animate_frame = fmod(animate_frame + frame_rate, v_pose.size());
		//drawnState = v_pose.at((int)animate_frame);
		//drawnState_n = v_pose.at( ((int)animate_frame + 1) % animation.size() );
	}
}

void Animation::addState() {
	if (v_pose.size() > 0) {
		v_pose.push_back( *copyState( (pose *)&v_pose.back() ) );
	}
	else {
		v_pose.push_back( *makeState() );
	}
	animate_frame = v_pose.size() - 1;
	//drawnState = animation.back();
	//drawnState_n = animation.back();
}

void Animation::setFrame(int i) {
	animate_frame = i;
	//drawnState = animation.at(i);
	//drawnState_n = animation.at(i);
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

void Animation::modSelection(int id, float x, float y, float z) {
	if ( id < 0 ) {
		return;
	}

	pose *p = &v_pose.at(animate_frame);
	p->angle->rotate( *new Quaternion (0, x, y, z) );



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


pose *Animation::makeState() {
	pose *next = new pose();
	int numBones = skeleton->getNumBones();
	next->angle = new Quaternion [ numBones ];

	for (int i = 0; i < numBones; ++i) {
		next->angle[i] = *new Quaternion(0, 0, 0, 1);
	}
	return next;
}

pose *Animation::copyState( pose *other ) {
	pose *next = new pose();
	int numBones = skeleton->getNumBones();
	next->angle = new Quaternion [ numBones ];

	for (int i = 0; i < numBones; ++i) {
		next->angle[i] = other->angle[i];
	}
	return next;
}

} /* namespace std */
