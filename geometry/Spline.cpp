/*
 * Spline.cpp
 *
 *  Created on: 29/08/2013
 *      Author: remnanjona
 */

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
		Vec3D i = point;
		glVertex3f(i.x, i.y, i.z);
	}
	glEnd();
}

} /* namespace std */
