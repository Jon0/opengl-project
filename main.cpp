/*
 * main.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <GL/glut.h>
#include "window/MainWindow.h"

using namespace std;

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);

	delete new MainWindow(800, 600);

	return EXIT_SUCCESS;
}


