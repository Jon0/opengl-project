/*
 * ViewSpline.cpp
 *
 *  Created on: 30/08/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <string>
#include <GL/glut.h>
#include "ViewSpline.h"

namespace std {

ViewSpline::ViewSpline():
		Ortho(),
		Spline(),
		points(),
		time(0) {
	play = false;
	time_f = 0.0;
	glPointSize(2.0);
}

ViewSpline::~ViewSpline() {
	// TODO Auto-generated destructor stub
}

int ViewSpline::mouseClicked(int button, int state, int x, int y) {
	if (button == 2 && state) {
		message.clear();
		message += "click ";
		message += to_string(x);
		message += ", ";
		message += to_string(y);

		points.push_back( *new Vec3D(x, y, 0) );
		equalise();
		return 1;
	}
	return 0;
}

int ViewSpline::mouseDragged(int x, int y) {
	return 0;
}

void ViewSpline::display(chrono::duration<double> tick) {
	displayline(0, (float)points.size() - 2.0);

	if (play) {
		time_f += 2.0; // getPointInc(time_f, 1.0); // tick
		Vec3D point = getDistPoint(time_f);
		glPushMatrix();
		glTranslatef(point.getX(), point.getY(), point.getZ());

		glColor3f(0.0, 1.0, 0.0);
		GLUquadric* q = gluNewQuadric();
		gluSphere(q, 10.0, 12, 12);
		glPopMatrix();
	}
}

void ViewSpline::messageSent(string s) {
	cout << s << endl;
	if (s == "play") {
		time_f = 0;
		time = time.zero();
		play = true;
	}
}

Vec3D ViewSpline::getKeyPoint(int i) {
	return points.at(i + 1);
}

int ViewSpline::getNumKeyFrames() {
	return points.size() - 2;
}

} /* namespace std */
