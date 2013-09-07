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

void Spline::displayline() {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	int length = getNumFrames();
	for (int i = 0; i < length; ++i) {
		Vec3D vec = getKeyPoint(i);
		glVertex3f(vec.getX(), vec.getY(), vec.getZ());
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (float u = 0; u < length; u += 0.01) {
		Vec3D v = getPoint(u);
		glVertex3f(v.getX(), v.getY(), v.getZ());
	}
	glEnd();

}

Vec3D Spline::getPoint(float u) {
	double part;
	double frac = modf(u, &part);
	int length = getNumFrames();

	int v = max(((int) part), 1);
	int vs[4];
	for (int i = 0; i < 4; ++i) {
		vs[i] = ( v-1 + i ) % length;
	}
	return catmull_rom(getKeyPoint(vs[0]), getKeyPoint(vs[1]), getKeyPoint(vs[2]), getKeyPoint(vs[3]), frac);
}

Vec3D Spline::catmull_rom(Vec3D a, Vec3D b, Vec3D c, Vec3D d, float u) {
	Vec3D v = b*2 + (c-a)*u + (a*2 - b*5 + c*4 - d)*pow(u, 2) + (b*3-c*3+d-a)*pow(u, 3);
	return v / 2.0;
}

} /* namespace std */
