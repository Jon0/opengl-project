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
	// TODO Auto-generated constructor stub
	glPointSize(4.0);
	glEnable(GL_POINTS);
}

Spline::~Spline() {
	// TODO Auto-generated destructor stub
}

void Spline::append(Vec3D &vec) {
	points.push_back(vec);
}

void Spline::display() {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	for (auto &point: points) {
		Vec3D vec = point;
		glVertex3f(vec.x, vec.y, vec.z);
	}
	glEnd();

	for (unsigned int v = 3; v < points.size(); ++v) {
		displayline((Vec3D)points.at(v-3), (Vec3D)points.at(v-2), (Vec3D)points.at(v-1), (Vec3D)points.at(v));
	}
}

void Spline::displayline(Vec3D a, Vec3D b, Vec3D c, Vec3D d) {
	glBegin(GL_LINE_STRIP);
	for (float u = 0; u < 1.0; u += 0.01) {
		Vec3D v = catmull_rom(a, b, c, d, u);
		glVertex3f(v.x/2.0, v.y/2.0, v.z/2.0);
	}
	glEnd();

}

Vec3D Spline::getPoint(float u) {
	double part;
	double frac = modf(u, &part);
	int v = (int) part;
	Vec3D g;
	if (v+3 < points.size()) {
		g = catmull_rom((Vec3D)points.at(v), (Vec3D)points.at(v+1), (Vec3D)points.at(v+2), (Vec3D)points.at(v+3), frac);
	}
	return g;

}

Vec3D Spline::catmull_rom(Vec3D a, Vec3D b, Vec3D c, Vec3D d, float u) {
	Vec3D v = b*2 + (c-a)*u + (a*2 - b*5 + c*4 - d)*pow(u, 2) + (b*3-c*3+d-a)*pow(u, 3);
	return v;
}

} /* namespace std */
