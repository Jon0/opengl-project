/*
 * main.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <GL/glut.h>
#include "scene/ViewSpline.h"

using namespace std;

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	ViewSpline view = ViewSpline();

	// start running
	glutMainLoop();
	return EXIT_SUCCESS;
}


