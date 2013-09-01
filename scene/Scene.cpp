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

void Scene::display() {
	skeleton->display();
}

Scene::~Scene() {
	delete skeleton;
}

} /* namespace std */
