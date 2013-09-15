/*
 * Teapot.cpp
 *
 *  Created on: 12/09/2013
 *      Author: remnanjona
 */

#include <GL/glut.h>
#include "Teapot.h"

namespace std {

Teapot::Teapot() {}

Teapot::~Teapot() {}

void Teapot::display() {
	glutSolidTeapot(12.0);
}

int Teapot::selectMouse(int, int) {
	return false;
}

} /* namespace std */
