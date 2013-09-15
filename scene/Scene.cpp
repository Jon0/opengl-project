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
		click_old{1, 0, 0, 0},
		click_new{1, 0, 0, 0},
		time() {
	playing = drag_bone = false;
	selectedBone = -1;
	clickx = clicky = 0;
	player.set_time( 0 );
}

Scene::~Scene() {}

void Scene::getBoneAlignment(Quaternion current, Quaternion cam_angle, Quaternion *result) {
	// reverse all existing rotations in order
	Quaternion k = cam_angle * *skeleton->getSelectionRot() * *skeleton->getBoneAxis(selectedBone);
	*result = k.multiplicativeInverse() * current * k;
}

int Scene::mouseSelect(int x, int y) {
	int sbone;
	glPushMatrix();
	player.apply_transform();
	sbone = skeleton->selectMouse(x, y);
	glPopMatrix();
	return sbone;
}

int Scene::mouseClicked(ViewInterface *view, int button, int state, int x, int y) {
	if (state) {
		drag_bone = false;
		clickx = 0;
		clicky = 0;
		return false;
	}

	if ((glutGetModifiers() & GLUT_ACTIVE_CTRL) == GLUT_ACTIVE_CTRL) {
		if (button == 0) {
			int bone = mouseSelect(x, y);
			selectedBone = (selectedBone == bone)? -1: bone;
		}
		return true;
	} else if (button == 0) {
		drag_bone = true;
		clickx = x;
		clicky = y;
	}
	else if (button == 2) {


		player.path->append( view->unProject(x, y) );
	}
	return true;
}

int Scene::mouseDragged( ViewInterface *in, int x, int y ) {
	if ( drag_bone && selectedBone >= 0 ) {
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
