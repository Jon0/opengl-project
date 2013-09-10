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

Spline::Spline(): u_delta() { delta  = 0.1; segments = 0.005; }

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

 Vec3D Spline::getDistPoint(float dist) {
	float mod = fmod(dist, segments);
	float percent = mod / segments;
	int seg_a = (int)( (dist - mod) / segments ) % ( u_delta.size() - 1 );


	float k = u_delta.at(seg_a) * (1 - percent) + u_delta.at(seg_a + 1) * percent;
	return getPoint( k );
 }

float Spline::getPointInc(float u, float dist_inc) {
	float mod = fmod(u, segments);
	float percent = mod / segments;

	int seg_a = (u - mod) / segments;
	//int dist = u_delta.at(seg_a) * (1 - percent);

	return u_delta.at(seg_a) * (1-percent) + u_delta.at(seg_a+1) * percent;
}

/* at point u on the spline find the increment
 * required to move forward the given distance */
float Spline::calcPointInc(float u, float dist_inc) {
	float u_inc = 0.005;
	Vec3D v1 = getPoint(u), v2 = getPoint(u+u_inc);
	float dist = v1.getDistance(v2);

	// move along arc
	while(dist < dist_inc) {
		u_inc += 0.005;
		v1 = v2;
		Vec3D v2 = getPoint(u+u_inc);
		dist += v1.getDistance(v2);
	}

	// distance is >= to dist_inc
	float ratio = (dist_inc / dist);
	return u_inc*ratio;
}

Vec3D Spline::catmull_rom(Vec3D a, Vec3D b, Vec3D c, Vec3D d, float u) {
	Vec3D v = b*2 + (c-a)*u + (a*2 - b*5 + c*4 - d)*pow(u, 2) + (b*3-c*3+d-a)*pow(u, 3);
	return v / 2.0;
}

/*
 * calculate a map between linear distance and u
 */
void Spline::equalise() {
	u_delta.clear();
	int length = getNumFrames();

	// distance | u
	// 0		| 0
	// 0.05		| 0.123
	// 0.10		| 0.521
	// etc

	for (float u = 0; u < length - 1;) {
		u_delta.push_back(u);
		u += calcPointInc(u, segments);
	}
	spline_length = u_delta.size() * segments;
}

} /* namespace std */
