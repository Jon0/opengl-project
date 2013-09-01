/*
 * Scene.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include "Scene.h"

namespace std {

Scene::Scene(): Camera() {
	skeleton = new Skeleton("assets/priman.asf", NULL);
}

Scene::~Scene() {
	delete skeleton;
}

void Scene::display() {
	skeleton->display();
}


} /* namespace std */
