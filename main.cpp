/*
 * main.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <memory>

#include "scene/GRender.h"

using namespace std;

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);

	shared_ptr<GRender> r{ new GRender() };
	r->start();

	// start running
	glutMainLoop();
	return EXIT_SUCCESS;
}


