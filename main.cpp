/*
 * main.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <GL/glut.h>
#include "scene/Scene.h"

using namespace std;

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	auto view = Scene("assets/priman.asf");

	// start running
	glutMainLoop();
	return EXIT_SUCCESS;
}


