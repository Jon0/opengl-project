/*
 * Path.cpp
 *
 *  Created on: 11/09/2013
 *      Author: remnanjona
 */

#include <GL/glut.h>
#include "../geometry/Skeleton.h"
#include "Path.h"

namespace std {

Path::Path():
		Spline(),
		points(),
		time(0) {
	play = false;
	glPointSize(2.0);
}

Path::~Path() {
	// TODO Auto-generated destructor stub
}

void Path::append(Vec3D point) {
	points.push_back(point);
	equalise();
}

void Path::display(chrono::duration<double> tick, Skeleton *s, pose *p) {
	displayline(0, (float)points.size() - 2.0);

	if (play) {
		time += tick;
		Vec3D point = getDistPoint(time.count());

		glPushMatrix();
		glTranslatef(point.getX(), point.getY(), point.getZ());

		//TODO: rotate by 2 quaternions from time and time+1 (0,x,y,z) and multiply

		s->display(p);

		glPopMatrix();

	} else {
		s->display(p);
	}
}

Vec3D Path::getKeyPoint(int i) {
	return points.at(i + 1);
}

int Path::getNumKeyFrames() {
	return points.size() - 2;
}

} /* namespace std */
