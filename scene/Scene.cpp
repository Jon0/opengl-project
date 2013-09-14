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

Scene::Scene(): time(0), sp() {
	playing = false;
	selectedBone = 0;
	clickx = clicky = 0;
	const char *filename = "assets/priman.asf";
	const char *filename_a = "assets/walk.amc";
	loader = new SkeletonLoader();
	aloader = new AnimationLoader();
	skeleton = loader->readASF((char *)filename);

	//animation = new Animation(skeleton);
	path = new Path();
	animation = aloader->readAMC(filename_a, skeleton, path);

	makeState(skeleton->getNumBones(), &current_pose);
	glPointSize(2.0);

	new Camera( this, new MainWindow(800, 600) );
}

Scene::~Scene() {
	delete skeleton;
}

void Scene::getBoneAlignment(Quaternion current, Quaternion cam_angle, Quaternion *result) {
	// reverse all existing rotations in order
	Quaternion k = cam_angle * *skeleton->getSelectionRot() * *skeleton->getBoneAxis(selectedBone);
	*result = k.multiplicativeInverse() * current * k;
}

int Scene::mouseClicked(ViewInterface *, int button, int state, int x, int y) {


	if (button == 0 && state) {
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

int Scene::mouseDragged( ViewInterface *in, int x, int y ) {
	if ( selectedBone >= 0 ) {
		GLdouble *p = skeleton->selectionCenter();
		Quaternion temp;

		// use old mouse position to find starting quaternion
		if (clickx > 0 && clicky > 0) {
			getArc( p[0], p[1], clickx, clicky, 200.0, &temp );
			getBoneAlignment(temp, in->cameraAngle(), &click_old);
			clickx = clicky = 0;
		}

		// modify bone orientation
		getArc( p[0], p[1], x, y, 200.0, &temp );
		getBoneAlignment(temp, in->cameraAngle(), &click_new);
		Quaternion drag = click_new * click_old.multiplicativeInverse();
		animation->modSelection(time.count(), selectedBone, drag);
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
		//animation->insertFrame();
	}
	else if (c == 'p') {
		cout << "play" << endl;
		playing = !playing;
	}
	else if (c == 'q') {
		cout << "reset" << endl;
		time = time.zero();
	}
	else if (c == 'w') {
		cout << "set frame" << endl;
		//int i = animation->getFrame() + 1;
		//animation->setFrame(i);
	}
	else if (c == 'b') {
		path->append(Vec3D(rand() % 80 - 40, rand() % 80 - 40, rand() % 80 - 40));
	}
}

void Scene::display( ViewInterface *in, chrono::duration<double> tick ) {
	if (playing) {
		time += tick * 20;
	}
	if (skeleton) {
		sp.setTimeDisplay(time.count());
		float d = sp.getDistanceValue(time.count()) * path->getArcLength() / sp.getTotalDistance();
		animation->update( time.count(), &current_pose );
		skeleton->setSelection( selectedBone );
		skeleton->setCurrentPose( &current_pose );
		path->translate( d, skeleton );
		path->displayline();
	}
}

void Scene::messageSent(string str) {

}


} /* namespace std */
