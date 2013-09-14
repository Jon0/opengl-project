/*
 * ViewSpline.cpp
 *
 *  Created on: 30/08/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <string>
#include "../geometry/Teapot.h"
#include "../window/MainWindow.h"
#include "../view/Ortho.h"
#include "ViewSpline.h"

namespace std {

ViewSpline::ViewSpline() {
	teapot = Teapot();
	message = "Skeleton";

	view = new Ortho( this, new MainWindow(800, 600) );
	acc = new Ortho( this, new MainWindow(400, 300) );
}

ViewSpline::~ViewSpline() {
	// TODO Auto-generated destructor stub
}

int ViewSpline::clickPrimary(int button, int state, int x, int y) {
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

int ViewSpline::clickSecondary(int button, int state, int x, int y) {
	Vec3D click(x, y, 0);
	if (button == 2 && state) {

		// TODO: sort new values, so order has increasing x

		speed.append( click );
		return 1;
	}
	return 0;
}

int ViewSpline::mouseClicked(ViewInterface *v, int button, int state, int x, int y) {
	if (v == view) {
		clickPrimary(button, state, x, y);
	}
	else {
		clickSecondary(button, state, x, y);
	}
	return 0;
}

int ViewSpline::mouseDragged(ViewInterface *v, int x, int y) {
	return 0;
}

void ViewSpline::display( ViewInterface *v, chrono::duration<double> tick ) {
	if (v == view) {
		path.displayline();
		path.translate(tick, &teapot);
		drawString(message);
	}
	else {
		speed.displayline();
	}
}

void ViewSpline::messageSent(string s) {
	cout << s << endl;
	if (s == "play") {
		path.play = true;
	}
}

} /* namespace std */
