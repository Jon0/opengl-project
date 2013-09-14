/*
 * main.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <GL/glut.h>
#include "scene/SpeedCurve.h"

using namespace std;

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	SpeedCurve view = SpeedCurve();

	// start running
	glutMainLoop();
	return EXIT_SUCCESS;
}


