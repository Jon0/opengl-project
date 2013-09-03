/*
 * Scene.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <iostream>
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

int Scene::clickInner(int x, int y) {
	clickx = x;
	clicky = y;
	selectedBone = skeleton->selectMouse(x, y, animation->currentPose());
	return false;
}

int Scene::dragInner(int x, int y) {
	if ( selectedBone >= 0 ) {
		animation->modSelection(selectedBone, x - clickx, y - clicky, 0);
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
		skeleton->setSelection(selectedBone);
		skeleton->display( animation->currentPose() );
		//animation->update( time );
	}
}


} /* namespace std */
