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

Spline::Spline(): distance(0.005) {

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
		glm::vec3 vec = getKeyPoint(i);
		glVertex3f(vec.x, vec.y, vec.z);
	}
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	length = getNumKeyFrames() - 1;
	for (float u = 0; u < length; u += 0.02) {
		glm::vec3 v = getPoint(u);
		//glColor3f(0.5 + sin(u * 2 * M_PI) / 2.0, 0.5 + cos(u * 2 * M_PI) / 2.0, 0);
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();
}

/*
 * u >= 0 only
 */
glm::vec3 Spline::getPoint(float u) {
	double part;
	double frac = modf(u, &part);
	int v = ((int) part ) % (getNumKeyFrames() - 1);
	return catmull_rom(getKeyPoint(v-1), getKeyPoint(v), getKeyPoint(v+1), getKeyPoint(v+2), frac);
}

glm::vec3 Spline::getDistPoint(float dist) {
	return getPoint( distance.getPoint(dist) );
 }

/* at point u on the spline find the increment
 * required to move forward the given distance */
float Spline::calcPointInc(float u, float dist_inc) {
	glm::vec3 v1, v2 = getPoint(u);
	float dist = 0, u_inc = 0;

	// TODO: binary search might be faster, and more accurate
	while(dist < dist_inc) {
		u_inc += 0.001;
		v1 = v2;
		v2 = getPoint(u+u_inc);
		dist += glm::distance(v1, v2);
	}

	// distance is >= to dist_inc
	//float ratio = (dist_inc / dist);
	return u_inc; // * ratio
}

glm::vec3 Spline::catmull_rom(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, float u) {
	glm::vec3 v = b*2.0f + (c-a)*u + (a*2.0f - b*5.0f + c*4.0f - d)*(float)pow(u, 2) + (b*3.0f-c*3.0f+d-a)*(float)pow(u, 3);
	return v / 2.0f;
}

/*
 * calculate a map between linear distance and u
 */
void Spline::equaliseLength() {
	distance.point.clear();

	// distance | u
	// 0		| 0
	// 0.05		| 0.123
	// 0.10		| 0.521
	// etc

	// TODO: only add new parts
	float ulength = getULength() - distance.segments;
	for (float u = 0; u < ulength;) {
		distance.point.push_back(u);
		u += calcPointInc(u, distance.segments);
	}
	spline_length = distance.point.size() * distance.segments;
}

} /* namespace std */
