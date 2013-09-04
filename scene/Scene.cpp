/*
 * Scene.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <math.h>
#include "Scene.h"

namespace std {

Scene::Scene(): Camera() {
	selectedBone = 0;
	clickx = clicky = 0;
	const char *filename = "assets/priman.asf";
	loader = new SkeletonLoader();
	skeleton = loader->readASF((char *)filename);
	animation = new Animation(skeleton);
}

Scene::~Scene() {
	delete skeleton;
}

void Scene::getBoneAlignment(Quaternion current, Quaternion *result) {
	// reverse all existing rotations in order
	Quaternion k = cam_angle * *skeleton->getSelectionRot() * *skeleton->getBoneAxis(selectedBone);
	*result = k.multiplicativeInverse() * current * k;
}

int Scene::clickInner(int x, int y) {
	if (button_state[0]) {
		if ( selectedBone >= 0 ) {
			GLdouble *p = skeleton->selectionCenter();
			int dx = x - p[0], dy = y - p[1];
			int d = sqrt(dx*dx + dy*dy);


			if ( d > 200.0 ) {
				selectedBone = skeleton->selectMouse(x, y, animation->currentPose());
			}
		}
		else {
			selectedBone = skeleton->selectMouse(x, y, animation->currentPose());
		}

	}

	clickx = x;
	clicky = y;


	// mouse wheel
	if (button_state[3]) {
		cout << "up" << endl;
		animation->rollSelection(selectedBone, 5.0);
	}
	else if (button_state[4]) {
		cout << "down" << endl;
		animation->rollSelection(selectedBone, -5.0);
	}

	return selectedBone >= 0;
}

int Scene::dragInner(int x, int y) {
	if ( selectedBone >= 0 ) {
		GLdouble *p = skeleton->selectionCenter();
		Quaternion temp;

		// use old mouse position to find starting quaternion
		if (clickx > 0 && clicky > 0) {
			getArc( p[0], p[1], clickx, clicky, 200.0, &temp );
			getBoneAlignment(temp, &click_old);
			clickx = clicky = 0;
		}

		// modify bone orientation
		getArc( p[0], p[1], x, y, 200.0, &temp );
		getBoneAlignment(temp, &click_new);
		Quaternion drag = click_new * click_old.multiplicativeInverse();
		animation->modSelection(selectedBone, drag);
		click_old = click_new;
		return true;
	}
	return false;
}

void Scene::keyPressed(unsigned char c) {
	if (c == 'a') {
		cout << "add state" << endl;
		animation->addState();
	}
	else if (c == 'p') {
		cout << "play" << endl;
		animation->animate(true);
	}
	else if (c == 'q') {
		cout << "reset" << endl;
		animation->setFrame(0);
	}
	else if (c == 'w') {
		int i = animation->getFrame() + 1;
		cout << "set frame " << i << endl;
		animation->setFrame(i);
	}
}

void Scene::display() {
	if (skeleton) {
		animation->update( 0.0 ); // TODO: use time
		skeleton->setSelection(selectedBone);
		skeleton->display( animation->currentPose() );
	}
}


} /* namespace std */
