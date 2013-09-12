/*
 * ViewSpline.cpp
 *
 *  Created on: 30/08/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <string>
#include <GL/glut.h>
#include "../geometry/Teapot.h"
#include "ViewSpline.h"

namespace std {

ViewSpline::ViewSpline(): Ortho() {
	d = new Teapot();
}

ViewSpline::~ViewSpline() {
	// TODO Auto-generated destructor stub
}

int ViewSpline::mouseClicked(int button, int state, int x, int y) {
	Vec3D click(x, y, 0);
	if (button == 2 && state) {
		message.clear();
		message += "click ";
		message += to_string(x);
		message += ", ";
		message += to_string(y);
		path.append( click );
		return 1;
	}
	else {
		int i = -1;
		float dist = 5;
		if ( path.getNearestPoint(click, &i, &dist) ) {
			cout << "select " << i << endl;
			return 1;
		}
	}
	return 0;
}

int ViewSpline::mouseDragged(int x, int y) {
	return 0;
}

void ViewSpline::display(chrono::duration<double> tick) {
	path.displayline();
	path.display(tick, d);
}

void ViewSpline::messageSent(string s) {
	cout << s << endl;
	if (s == "play") {
		path.play = true;
	}
}

} /* namespace std */
