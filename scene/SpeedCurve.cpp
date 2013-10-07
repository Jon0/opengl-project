/*
 * SpeedCurve.cpp
 *
 *  Created on: 14/09/2013
 *      Author: remnanjona
 */

#include <algorithm>
#include "SpeedCurve.h"

namespace std {

SpeedCurve::SpeedCurve():
		mWnd{new MainWindow(1000, 200, "Speed Curve")},
		speed(),
		values(),
		distance() {
	mWnd->start();
	reset();
}

SpeedCurve::~SpeedCurve() {}

void SpeedCurve::reset() {
	dragSelection = false;
	pmx = pmy = 0;
	total_distance = 0.0;
	time = 0.0;
	values_dx = 10.0;
	values.clear();
	distance.clear();
	speed.points.clear();
}

void SpeedCurve::calculateValues() {
	if (speed.points.size() < 4) return;
	float ud = 0.005; // accuracy of approximation
	total_distance = 0.0;
	values.clear();
	distance.clear();

	/* initial point */
	values.push_back( speed.getPoint(0).getY() );
	distance.push_back( 0.0 );

	float x = speed.getPoint(0).getX() + values_dx;
	float k = speed.getPoint(speed.getULength() - ud).getX();
	float u = 0;
	for (; x < k; x += values_dx) {
		while (speed.getPoint(u).getX() < x) {
			u += ud;
		}
		values.push_back( speed.getPoint(u).getY() );

		/* work distance covers */
		float a = values.at( values.size() - 2 );
		float b = values.at( values.size() - 1 );
		total_distance += values_dx * (a + b) / 2.0;
		distance.push_back(total_distance);
	}
}

void SpeedCurve::setTimeDisplay(float t) {
	time = t;
}

float SpeedCurve::getSpeedValue(float time) {
	float mod = fmod(time, values_dx);
	float percent = mod / values_dx;
	int seg_a = (int)( (time - mod) / values_dx ) % ( values.size() - 1 );

	return values.at(seg_a) * (1 - percent) + values.at(seg_a + 1) * percent;
}

float SpeedCurve::getDistanceValue(float time) {
	if (distance.size() < 1) return 0;

	float mod = fmod(time, values_dx);
	float percent = mod / values_dx;
	int seg_a = (int)( (time - mod) / values_dx ) % ( values.size() - 1 );

	return (distance.at(seg_a) * (1 - percent) + distance.at(seg_a + 1) * percent);
}

float SpeedCurve::getTotalDistance() {
	return total_distance;
}

void SpeedCurve::prepare() {
	// do nothing
}


void SpeedCurve::display( shared_ptr<ViewInterface>, chrono::duration<double> ) {
	speed.displayline();

	if (speed.getNumKeyFrames() > 1) {
		float modTime = fmod(time, values_dx * (values.size() - 1));
		float x = speed.getPoint(0).getX();

		glBegin(GL_LINES);
		glColor3f(0.2, 0.2, 0.2);
		for (unsigned int i = 0; i < values.size(); ++i) {
			glVertex3f(x + i * values_dx, 0, 0);
			glVertex3f(x + i * values_dx, 600, 0);
		}
		glColor3f(0.2, 0.8, 0.2);
		glVertex3f(x + modTime, 0, 0);
		glVertex3f(x + modTime, 600, 0);
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		glPointSize(3.0);
		glBegin(GL_POINTS);
		for (unsigned int i = 0; i < values.size(); ++i) {
			glVertex3f(x + i * values_dx, values.data()[i], 0);
		}
		glEnd();

		drawString("Speed: "+to_string( getSpeedValue(modTime)), 5, 180 );
	}

	glColor3f(0.7, 0.0, 0.7);
	glPointSize(8.0);
	glBegin(GL_POINTS);
	for (unsigned int i = 0; i < speed.points.size(); ++i) {
		auto *v = speed.points.data()[i].v;
		glVertex3f(v[0], v[1], v[2]);
	}
	glEnd();
}

void SpeedCurve::displayUI() {

}

void SpeedCurve::displayGeometry() {

}

int SpeedCurve::mouseClicked(shared_ptr<ViewInterface> v, int button, int state, int x, int y) {
	Vec3D click(x, y, 0);
	if (!state) {

		/* get nearby points */
		float distance = 30;
		selection = -1;
		for ( unsigned int i = 0; i < speed.points.size(); ++i ) {
			float dt = speed.points[i].getDistance({ (float)x, (float)y, 0 });
			if (dt < distance) {
				selection = i;
				distance = dt;
			}
		}
		if (selection < 0) {
			// sort new values, so order has increasing x
			speed.points.push_back( click );
			inplace_merge(begin(speed.points), speed.points.end() - 1, speed.points.end(), vec_comp_x);
			calculateValues();
		}
		else {
			dragSelection = true;
			pmx = x;
			pmy = y;

		}
		return 1;
	}
	else {
		dragSelection = false;
		calculateValues();
	}
	return 0;
}

int SpeedCurve::mouseDragged(shared_ptr<ViewInterface>, int x, int y) {
	/*
	 * drag selected data point
	 */
	if (dragSelection) {
		speed.points.data()[selection].v[0] += x - pmx;
		speed.points.data()[selection].v[1] += y - pmy;
		pmx = x;
		pmy = y;
		return true;
	}
	return false;
}

void SpeedCurve::messageSent(string) {

}

void SpeedCurve::keyPressed(unsigned char) {

}

bool vec_comp_x(const Vec3D &a, const Vec3D &b) {
	return a.getX() < b.getX();
}

} /* namespace std */
