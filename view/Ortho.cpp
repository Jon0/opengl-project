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
	view_width = 1;
	view_height = 1;
	message = "Skeleton";
}

Ortho::~Ortho() {
	// TODO Auto-generated destructor stub
}

void Ortho::setView() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, view_width, 0.0, view_height, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw scene
	display();

	// draw text
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(0.0, 0.0);
	const char *str = message.c_str();
	int len = (int) strlen(str);
	void *font = GLUT_BITMAP_HELVETICA_18;
	glutBitmapCharacter(font, '>');
	glutBitmapCharacter(font, ' ');
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(font, str[i]);
	}
}

void Ortho::resize(int x, int y) {
	view_width = x;
	view_height = y;
}

void Ortho::keyPressed(unsigned char c) {
	if (c == '\r') {
		messageSent(message);
		message.clear();
	}
	else {
		message += c;	// string append
	}
}

} /* namespace std */
