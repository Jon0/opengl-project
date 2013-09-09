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

void Spline::displayline(float a, float b) {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	int length = getNumFrames();
	for (int i = 0; i < length; ++i) {
		Vec3D vec = getKeyPoint(i);
		glVertex3f(vec.getX(), vec.getY(), vec.getZ());
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (float u = a; u < b; u += 0.02) {
		Vec3D v = getPoint(u);
		//glColor3f(0.5 + sin(u * 2 * M_PI) / 2.0, 0.5 + cos(u * 2 * M_PI) / 2.0, 0);
		glVertex3f(v.getX(), v.getY(), v.getZ());
	}
	glEnd();

}

/*
 * u >= 0 only
 */
Vec3D Spline::getPoint(float u) {
	double part;
	double frac = modf(u, &part);
	int length = getNumFrames();
	int vs[4];
	vs[1] = ((int) part ) % length;
	vs[0] = max( vs[1]-1, 0 );
	vs[2] = min( vs[1]+1, length-1 );
	vs[3] = min( vs[1]+2, length-1 );
	return catmull_rom(getKeyPoint(vs[0]), getKeyPoint(vs[1]), getKeyPoint(vs[2]), getKeyPoint(vs[3]), frac);
}

float Spline::getPointInc(float u, float inc) {
	Vec3D v1 = getPoint(u);

	float u_inc = 0.005;
	Vec3D v2 = getPoint(u+u_inc);
	float dist = v1.getDistance(v2);
	while(dist < inc) {
		u_inc += 0.005;
		v1 = v2;
		Vec3D v2 = getPoint(u+u_inc);
		dist += v1.getDistance(v2);
	}




	return  u_inc * (dist / inc);
	//return v1*(1-ratio) + v2*ratio;
}

Vec3D Spline::catmull_rom(Vec3D a, Vec3D b, Vec3D c, Vec3D d, float u) {
	Vec3D v = b*2 + (c-a)*u + (a*2 - b*5 + c*4 - d)*pow(u, 2) + (b*3-c*3+d-a)*pow(u, 3);
	return v / 2.0;
}

void Spline::equalise() {
	float delta = 0.01;
	int length = getNumFrames();
	for (float i = 0; i < length; ++delta) {
		Vec3D v1 = getPoint(i);
		Vec3D v2 = getPoint(i+0.01);

		//v1.
	}
}

} /* namespace std */
