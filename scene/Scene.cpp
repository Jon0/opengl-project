/*
 * Scene.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include "Scene.h"

namespace std {

Scene::Scene(): Camera() {
	clickx = clicky = 0;
	const char *filename = "assets/priman.asf";
	loader = new SkeletonLoader();
	skeleton = loader->readASF((char *)filename);
}

Scene::~Scene() {
	delete skeleton;
}

int Scene::clickInner(int x, int y) {
	clickx = x;
	clicky = y;
	skeleton->selectMouse(x, y, getProjMatrix(), getModelMatrix());
	return false;
}

int Scene::dragInner(int x, int y) {
	if ( skeleton->hasSelection() ) {
		skeleton->modSelection(x - clickx, y - clicky, 0);
		clickx = x;
		clicky = y;
		return true;
	}

	return false;
}

void Scene::display() {
	if (skeleton) {
		skeleton->display();
	}
}


} /* namespace std */
