/*
 * Spline.cpp
 *
 *  Created on: 29/08/2013
 *      Author: remnanjona
 */

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

	for (int v = 3; v < points.size(); ++v) {
		Vec3D i = points.at(v-3);
		Vec3D j = points.at(v-2);
		Vec3D k = points.at(v-1);
		Vec3D l = points.at(v);
		displayline(i, j, k, l);
	}
}

void Spline::displayline(Vec3D a, Vec3D b, Vec3D c, Vec3D d) {
	glBegin(GL_LINES);
	glVertex3f(b.x, b.y, b.z);
	for (float u = 0; u < 1.0; u += 0.01) {
		//Vec3D v = b*(1-u) + c*u;
		//Vec3D v = a*pow(1-u, 3) + b*3*u*pow(1-u, 2) + c*3*pow(u, 2)*(1-u) + d*pow(u, 3);
		Vec3D v = b*2 + (c-a)*u + (a*2 - b*5 + c*4 - d)*pow(u, 2) + (b*3-c*3+d-a)*pow(u, 3);
		glVertex3f(v.x/2.0, v.y/2.0, v.z/2.0);
		glVertex3f(v.x/2.0, v.y/2.0, v.z/2.0);
	}
	glVertex3f(c.x, c.y, c.z);
	glEnd();

}

} /* namespace std */
