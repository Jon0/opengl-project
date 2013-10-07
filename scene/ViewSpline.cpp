/*
 * ViewSpline.cpp
 *
 *  Created on: 30/08/2013
 *      Author: remnanjona
 */

#include <string>
#include "../geometry/Teapot.h"
#include "../window/MainWindow.h"
#include "../view/Ortho.h"
#include "ViewSpline.h"

namespace std {

ViewSpline::ViewSpline():
		mWnd{ new MainWindow(800, 600, "Spline") },
		teapot{ new Teapot() },
		sp{} {
	mWnd->start();
	play = false;
	message = "Skeleton";
}

ViewSpline::~ViewSpline() {}

int ViewSpline::mouseClicked(shared_ptr<ViewInterface> v, int button, int state, int x, int y) {
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
			return 1;
		}

	}
	return 0;
}

int ViewSpline::mouseDragged(shared_ptr<ViewInterface> v, int x, int y) {
	return 0;
}

void ViewSpline::prepare() {
	// do nothing
}

void ViewSpline::display(shared_ptr<ViewInterface> v, chrono::duration<double> tick) {
	if (play) {
		time += tick * 10;
	}
	sp.setTimeDisplay(time.count());
	float d = sp.getDistanceValue(time.count()) * path.getArcLength() / sp.getTotalDistance();
	path.displayline();

	glPushMatrix();
	path.translate( d );
	teapot->display();
	glPopMatrix();

	drawString( message, 10, 10 );
}

void ViewSpline::messageSent(string s) {
	if (s == "play") {
		play = true;
	}
}

void ViewSpline::keyPressed(unsigned char) {

}

} /* namespace std */
