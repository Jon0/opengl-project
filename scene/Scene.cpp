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

Scene::Scene(): Camera(), time(0) {
	playing = false;
	selectedBone = 0;
	clickx = clicky = 0;
	const char *filename = "assets/priman.asf";
	const char *filename_a = "assets/walk.amc";
	loader = new SkeletonLoader();
	aloader = new AnimationLoader();
	skeleton = loader->readASF((char *)filename);
	animation = aloader->readAMC(filename_a, skeleton);
	//animation = new Animation(skeleton);
	path = new Path();
	makeState(skeleton->getNumBones(), &p);
	glPointSize(2.0);
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
				//*skeleton->getPose() = *animation->currentPose();
				selectedBone = skeleton->selectMouse(x, y);
			}
		}
		else {
			//*skeleton->getPose() = *animation->currentPose();
			selectedBone = skeleton->selectMouse(x, y);
		}

	}

	clickx = x;
	clicky = y;


	// mouse wheel
	//if (button_state[3]) {
	//	animation->rollSelection(selectedBone, 5.0);
	//}
	//else if (button_state[4]) {
	//	animation->rollSelection(selectedBone, -5.0);
	//}

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
		cout << "add frame" << endl;
		animation->addFrame();
	}
	else if (c == 's') {
		cout << "insert frame" << endl;
		animation->insertFrame();
	}
	else if (c == 'p') {
		cout << "play" << endl;
		animation->animate(true);
		path->play = true;
		playing = !playing;
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
	else if (c == 'b') {
		path->append(Vec3D(rand() % 80 - 40, rand() % 80 - 40, rand() % 80 - 40));
	}
}

void Scene::display(chrono::duration<double> tick) {
	if (playing) {
		time += tick * 25;
	}
	if (skeleton) {
		animation->update( time.count(), &p ); // TODO: use time
		skeleton->setSelection( selectedBone );
		skeleton->setCurrentPose( &p );
		path->display( tick, skeleton );
	}
}


} /* namespace std */
