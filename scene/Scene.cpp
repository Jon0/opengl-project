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
	click_q = NULL;
	roll = 0.0;
	const char *filename = "assets/priman.asf";
	loader = new SkeletonLoader();
	skeleton = loader->readASF((char *)filename);
	animation = new Animation(skeleton);
}

Scene::~Scene() {
	delete skeleton;
}

int Scene::clickInner(int x, int y) {
	if (button_state[0]) {
		if ( selectedBone >= 0 ) {
			GLdouble *p = skeleton->selectionCenter();
			int dx = x - p[0], dy = y - p[1];
			int d = sqrt(dx*dx + dy*dy);

			// mouse wheel
			if (button_state[3]) {
				cout << "up" << endl;
				animation->rollSelection(selectedBone, 5.0);
			}
			else if (button_state[4]) {
				cout << "down" << endl;
				animation->rollSelection(selectedBone, -5.0);
			}
			if ( d > 200.0 ) {
				selectedBone = skeleton->selectMouse(x, y, animation->currentPose());
			}
		}
		else {
			selectedBone = skeleton->selectMouse(x, y, animation->currentPose());
		}

	}
	click_q = NULL;
	clickx = x;
	clicky = y;
	return selectedBone >= 0;
}

int Scene::dragInner(int x, int y) {
	if ( selectedBone >= 0 ) {
		GLdouble *p = skeleton->selectionCenter();
		Quaternion *current = getArc(p[0], p[1], x, y, 200.0);

		Quaternion j = cam_angle->multiplicativeInverse();
		current->rotate( j );

		Quaternion i = skeleton->getBoneRot(selectedBone)->multiplicativeInverse();
		current->rotate( i );

		if (click_q) {
			Quaternion drag = *current * click_q->multiplicativeInverse();
			Quaternion k = *skeleton->getSelectionRot();
			Quaternion a = k * drag * k.multiplicativeInverse();
			animation->modSelection(selectedBone, a);

		}
		click_q = current;
		//animation->modSelection(selectedBone, (x - clickx)/ 20.0, (y - clicky)/ 20.0, 0);
		clickx = x;
		clicky = y;
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
