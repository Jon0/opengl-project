/*
 * main.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <memory>
#include <GL/glut.h>
#include "scene/Scene.h"

using namespace std;

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	shared_ptr<Scene> r{ new Scene("assets/priman.asf") };
	r->start();

	// start running
	glutMainLoop();
	return EXIT_SUCCESS;
}


