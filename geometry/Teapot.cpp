/*
 * Teapot.cpp
 *
 *  Created on: 12/09/2013
 *      Author: remnanjona
 */

#include <GL/glut.h>
#include "Teapot.h"

namespace std {

Teapot::Teapot() {
	// TODO Auto-generated constructor stub
}

Teapot::~Teapot() {
	// TODO Auto-generated destructor stub
}

void Teapot::display() {
	glutSolidTeapot(12.0);
}

} /* namespace std */
