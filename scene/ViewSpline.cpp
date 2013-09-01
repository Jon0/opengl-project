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

ViewSpline::ViewSpline(): Ortho() {
	spline = new Spline();
	time = 0.0;
	play = false;
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
		spline->append(*new Vec3D(x, y, 0));
		return 1;
	}
	return 0;
}

int ViewSpline::mouseDragged(int x, int y) {
	return 0;
}

void ViewSpline::display() {
	spline->display();

	if (play) {
		Vec3D point = spline->getPoint(time);
		//cout << point.x << ", " << point.y << endl;
		glPushMatrix();
		glTranslatef(point.x/2, point.y/2, 0);

		glColor3f(0.0, 1.0, 0.0);
		GLUquadric* q = gluNewQuadric();
		gluSphere(q, 10.0, 12, 12);
		glPopMatrix();

		time += 0.01;
	}
}

void ViewSpline::messageSent(string s) {
	cout << s << endl;
	if (s == "play") {
		time = 0.0;
		play = true;
	}
}

} /* namespace std */
