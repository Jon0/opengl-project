/*
 * SpeedCurve.cpp
 *
 *  Created on: 14/09/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <algorithm>
#include "../window/MainWindow.h"
#include "../view/Ortho.h"
#include "SpeedCurve.h"

namespace std {

SpeedCurve::SpeedCurve(): values() {
	values_dx = 10.0;

	view = new Ortho( this, new MainWindow(800, 200) );
}

SpeedCurve::~SpeedCurve() {
	// TODO Auto-generated destructor stub
}

void SpeedCurve::calculateValues() {
	if (speed.points.size() < 4) return;
	values.clear();

	float x = speed.getPoint(0).getX();
	float k = speed.getPoint(speed.getULength() - 0.005).getX();
	float u = 0;
	for (; x < k; x += values_dx) {
		while (speed.getPoint(u).getX() < x) {
			u += 0.005;
		}
		values.push_back( speed.getPoint(u).getY() );
	}
}

void SpeedCurve::display( ViewInterface *, chrono::duration<double> ) {
	speed.displayline();

	if (speed.getNumKeyFrames() > 1) {
		float x = speed.getPoint(0).getX();
		glColor3f(0.2, 0.2, 0.2);
		glBegin(GL_LINES);
		for (unsigned int i = 0; i < values.size(); ++i) {
			glVertex3f(x + i * values_dx, 0, 0);
			glVertex3f(x + i * values_dx, 600, 0);
		}
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		glPointSize(5.0);
		glBegin(GL_POINTS);
		for (unsigned int i = 0; i < values.size(); ++i) {
			glVertex3f(x + i * values_dx, values.data()[i], 0);
		}
		glEnd();

	}
}

int SpeedCurve::mouseClicked(ViewInterface *v, int button, int state, int x, int y) {
	Vec3D click(x, y, 0);
	if (button == 2 && state) {

		// TODO: sort new values, so order has increasing x

		speed.points.push_back( click );
		inplace_merge(speed.points.begin(), speed.points.end(), speed.points.end() + 1, vec_comp_x);
		calculateValues();
		return 1;
	}
	return 0;
}

int SpeedCurve::mouseDragged(ViewInterface *, int x, int y) {
	return false;
}

void SpeedCurve::messageSent(string) {

}

bool vec_comp_x(Vec3D a, Vec3D b) {
	return a.getX() < b.getX();
}

} /* namespace std */
