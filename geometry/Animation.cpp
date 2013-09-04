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

	current.angle = new Quaternion [ s->getNumBones() ];
	addState();
}

Animation::~Animation() {
	// TODO Auto-generated destructor stub
}

pose *Animation::currentPose() {
	return &current;
}

Vec3D *Animation::getCentre() {
	return &current.position;
}

void Animation::update(float time) {
	if (show_animate && v_pose.size() > 0) {

		// set correct pose base on keyframes
		animate_frame = fmod( animate_frame + frame_rate, v_pose.size() );
		pose *a = &v_pose.at( (int) animate_frame );
		pose *b = &v_pose.at( ((int) animate_frame + 1) % v_pose.size() );
		float t = fmod(animate_frame, 1.0);
		int numBones = skeleton->getNumBones();

		for (int i = 0; i < numBones; ++i) {
			current.angle[i] = slerp(a->angle[i], b->angle[i], t);
		}
	}
	else {
		setCurrentPose( (pose *)&v_pose.at( (int) animate_frame ) );
	}
}

void Animation::addState() {
	if (v_pose.size() > 0) {
		v_pose.push_back( *copyState( skeleton->getNumBones(), (pose *)&v_pose.back() ) );
	}
	else {
		v_pose.push_back( *makeState( skeleton->getNumBones() ) );
	}
	animate_frame = v_pose.size() - 1;
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

	pose *p = &v_pose.at(animate_frame);
	Vec3D v = p->angle[id].vector();
	Quaternion q(f, v);
	Quaternion k = *skeleton->getBoneRot(id) * q.multiplicativeInverse();

	p->angle[id].rotate( k );

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

void Animation::setCurrentPose(pose *p) {
	current.position = p->position;
	for (int i = 0; i < skeleton->getNumBones(); ++i) {
		current.angle[i] = p->angle[i];
	}
}

pose *makeState( int numBones ) {
	pose *next = new pose();
	next->position = Vec3D(0, 0, 0);
	next->angle = new Quaternion [ numBones ];

	for (int i = 0; i < numBones; ++i) {
		next->angle[i] = *new Quaternion(1, 0, 0, 0);
	}
	return next;
}

pose *copyState( int numBones, pose *other ) {
	pose *next = new pose();
	next->position = other->position;
	next->angle = new Quaternion [ numBones ];

	for (int i = 0; i < numBones; ++i) {
		next->angle[i] = *new Quaternion( other->angle[i] );
	}
	return next;
}

} /* namespace std */
