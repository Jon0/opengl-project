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
		mWnd{new MainWindow(800, 600, "Scene")},
		camera{ new Camera( this, mWnd ) },
		ortho{ new Ortho( this, mWnd ) },
		loader{ new SkeletonLoader() },
		skeleton{ loader->readASF( filename.c_str() ) },
		player{skeleton, "assets/walk.amc"},
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

}

void Scene::display( ViewInterface *in, chrono::duration<double> tick ) {
	if (in == camera.get()) {
		if (playing) {
			time += tick * 30;
		}
		if (skeleton) {
			player.set_time(time.count());
			skeleton->setSelection(selectedBone);

			glPushMatrix();
			player.apply_transform();
			skeleton->display();
			glPopMatrix();

			player.path->displayline();
		}
	}
}

void Scene::messageSent(string str) {
	cout << str << endl;
	if (str == "add") {
		player.animation[0].addFrame();
	}
	else if (str == "play") {
		playing = !playing;
	}
	else if (str == "reset") {
		time = time.zero();
		player.reset();
	}
	else if (str.substr(0, 4) == "load") {
		string name = "assets/"+str.substr(5)+".amc";
		cout << name << endl;
		player.loadFile(name);
	}

	else if (str == "x") {
		player.set_pose_seq(0);
	}
	else if (str == "c") {
		player.set_pose_seq(1);
	}

	else if (str == "set frame") {
		//int i = animation->getFrame();
		//animation->setFrame(i);
	}
	else if (str == "insert frame") {
		//animation->insertFrame();
	}
}


} /* namespace std */
