/*
 * Ortho.cpp
 *
 *  Created on: 26/08/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <string.h>
#include <GL/glut.h>
#include "Ortho.h"

namespace std {

Ortho::Ortho() {
	spline = new Spline();
	message = "> Skeleton";
}

Ortho::~Ortho() {
	// TODO Auto-generated destructor stub
}

void Ortho::setView() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Ortho::display() {
	setView();

	// draw spline
	spline->display();

	// draw text
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(0.0, 0.0);
	const char *str = message.c_str();
	int len = (int) strlen(str);
	void *font = GLUT_BITMAP_HELVETICA_18;
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(font, str[i]);
	}
}

void Ortho::keyPressed(unsigned char c) {
	if (c == '\r') {
		message.clear();
		message += "> ";
	}
	else {
		message += c;	// string append
	}
}

void Ortho::mouseClicked(int button, int state, int x, int y) {
	if (button >= 0 && state) {
		cout << x << ", " << y << endl;
		message.clear();
		message += "> click ";
		message += to_string(x);
		message += ", ";
		message += to_string(y);
		spline->append(*new Vec3D(x, y, 0));
	}
}

} /* namespace std */
