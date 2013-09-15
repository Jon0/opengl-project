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

Scene::Scene(string filename):
		camera{ new Camera( this, new MainWindow(800, 600, "Scene") ) },
		loader{ new SkeletonLoader() },
		skeleton{ loader->readASF( filename.c_str() ) },
		player(skeleton, "assets/walk.amc"),
		time() {
	playing = false;
	selectedBone = clickx = clicky = 0;
	player.set_time( 0 );
}

Scene::~Scene() {}

void Scene::getBoneAlignment(Quaternion current, Quaternion cam_angle, Quaternion *result) {
	// reverse all existing rotations in order
	Quaternion k = cam_angle * *skeleton->getSelectionRot() * *skeleton->getBoneAxis(selectedBone);
	*result = k.multiplicativeInverse() * current * k;
}

void Scene::mouseSelect(int x, int y) {
	glPushMatrix();
	player.apply_transform();
	selectedBone = skeleton->selectMouse(x, y);
	glPopMatrix();
}

int Scene::mouseClicked(ViewInterface *, int button, int state, int x, int y) {
	if (button == 0 && state) {
		if ( selectedBone >= 0 ) {
			GLdouble *p = skeleton->selectionCenter();
			int dx = x - p[0], dy = y - p[1];
			int d = sqrt(dx*dx + dy*dy);
			if ( d > 200.0 ) {
				mouseSelect(x, y);
			}
		}
		else {
			mouseSelect(x, y);
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
		player.animation[0].modSelection( time.count(), selectedBone, drag );
		click_old = click_new;
		return true;
	}
	return false;
}

void Scene::keyPressed(unsigned char c) {
	if (c == 'a') {
		cout << "add frame" << endl;
		player.animation[0].addFrame();
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
		player.path->append(Vec3D(rand() % 80 - 40, rand() % 80 - 40, rand() % 80 - 40));
	}
	else if (c == 'x') {
		player.set_pose_seq(0);
	}
	else if (c == 'c') {
		player.set_pose_seq(1);
	}
}

void Scene::display( ViewInterface *in, chrono::duration<double> tick ) {
	if (playing) {
		time += tick * 30;
	}
	if (skeleton) {
		player.set_time( time.count() );
		skeleton->setSelection( selectedBone );

		glPushMatrix();
		player.apply_transform();
		skeleton->display();
		glPopMatrix();

		player.path->displayline();
	}
}

void Scene::messageSent(string str) {

}


} /* namespace std */
