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

ViewSpline::ViewSpline(): sp() {
	play = false;
	teapot = Teapot();
	message = "Skeleton";
	view = new Ortho( this, new MainWindow(800, 600) );
}

ViewSpline::~ViewSpline() {
	// TODO Auto-generated destructor stub
}

int ViewSpline::mouseClicked(ViewInterface *v, int button, int state, int x, int y) {
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

int ViewSpline::mouseDragged(ViewInterface *v, int x, int y) {
	return 0;
}

// TODO: display speed increments
void ViewSpline::display(ViewInterface *v, chrono::duration<double> tick) {
	if (play) {
		time += tick * 10;
	}
	sp.setTimeDisplay(time.count());
	float d = sp.getDistanceValue(time.count()) * path.getArcLength() / sp.getTotalDistance();
	path.displayline();
	path.translate(d, &teapot);
	drawString(message);
}

void ViewSpline::messageSent(string s) {
	cout << s << endl;
	if (s == "play") {
		play = true;
	}
}

void ViewSpline::keyPressed(unsigned char) {

}

} /* namespace std */
