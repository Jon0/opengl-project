/*
 * Spline.cpp
 *
 *  Created on: 29/08/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include "Spline.h"

namespace std {

Spline::Spline() {

}

Spline::~Spline() {
	// TODO Auto-generated destructor stub
}

void Spline::displayline() {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	int length = getNumFrames();
	for (int i = 0; i < length; ++i) {
		Vec3D vec = getKeyPoint(i);
		glVertex3f(vec.x, vec.y, vec.z);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (float u = 0; u < length; u += 0.01) {
		Vec3D v = getPoint(u);
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();

}

Vec3D Spline::getPoint(float u) {
	double part;
	double frac = modf(u, &part);
	int v = (int) part;
	Vec3D g;
	if ( v+3 < getNumFrames() ) {
		g = catmull_rom(getKeyPoint(v), getKeyPoint(v+1), getKeyPoint(v+2), getKeyPoint(v+3), frac);
	}
	return g;

}

Vec3D Spline::catmull_rom(Vec3D a, Vec3D b, Vec3D c, Vec3D d, float u) {
	Vec3D v = b*2 + (c-a)*u + (a*2 - b*5 + c*4 - d)*pow(u, 2) + (b*3-c*3+d-a)*pow(u, 3);
	return v / 2;
}

} /* namespace std */
