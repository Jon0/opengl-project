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

Spline::Spline(): u_delta() {
	segments = 0.005;
	spline_length = 0.0;
}

float Spline::getULength() {
	return (getNumKeyFrames() - 1);
}

float Spline::getArcLength() {
	return spline_length;
}

void Spline::displayline() {
	glColor3f(0.7, 0.7, 0.0);
	glPointSize(8.0);
	glBegin(GL_POINTS);

	int length = getNumKeyFrames() + 1;
	for (int i = -1; i < length; ++i) {
		Vec3D vec = getKeyPoint(i);
		glVertex3f(vec.getX(), vec.getY(), vec.getZ());
	}
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	length = getNumKeyFrames() - 1;
	for (float u = 0; u < length; u += 0.02) {
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
	int v = ((int) part ) % (getNumKeyFrames() - 1);
	return catmull_rom(getKeyPoint(v-1), getKeyPoint(v), getKeyPoint(v+1), getKeyPoint(v+2), frac);
}

 Vec3D Spline::getDistPoint(float dist) {
	float mod = fmod(dist, segments);
	float percent = mod / segments;
	int seg_a = (int)( (dist - mod) / segments ) % ( u_delta.size() - 1 );

	float k = u_delta.at(seg_a) * (1 - percent) + u_delta.at(seg_a + 1) * percent;
	return getPoint( k );
 }

/* at point u on the spline find the increment
 * required to move forward the given distance */
float Spline::calcPointInc(float u, float dist_inc) {
	Vec3D v1, v2 = getPoint(u);
	float dist = 0, u_inc = 0;

	// TODO: binary search might be faster, and more accurate
	while(dist < dist_inc) {
		u_inc += 0.001;
		v1 = v2;
		v2 = getPoint(u+u_inc);
		dist += v1.getDistance(v2);
	}

	// distance is >= to dist_inc
	//float ratio = (dist_inc / dist);
	return u_inc; // * ratio
}

Vec3D Spline::catmull_rom(Vec3D a, Vec3D b, Vec3D c, Vec3D d, float u) {
	Vec3D v = b*2 + (c-a)*u + (a*2 - b*5 + c*4 - d)*pow(u, 2) + (b*3-c*3+d-a)*pow(u, 3);
	return v / 2.0;
}

/*
 * calculate a map between linear distance and u
 */
void Spline::equaliseLength() {
	u_delta.clear();

	// distance | u
	// 0		| 0
	// 0.05		| 0.123
	// 0.10		| 0.521
	// etc

	// TODO: only add new parts
	float ulength = getULength() - segments;
	for (float u = 0; u < ulength;) {
		u_delta.push_back(u);
		u += calcPointInc(u, segments);
	}
	spline_length = u_delta.size() * segments;
}

} /* namespace std */
