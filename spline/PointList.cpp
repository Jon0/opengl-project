/*
 * PointList.cpp
 *
 *  Created on: 7/09/2013
 *      Author: remnanjona
 */

#include <GL/glut.h>
#include "PointList.h"

namespace std {

PointList::PointList(): points() {
	glPointSize(2.0);
	glEnable(GL_POINTS);
}

PointList::~PointList() {
	// TODO Auto-generated destructor stub
}

void PointList::display() {
	displayline(1, (float)points.size() - 2.0);
}

void PointList::append(Vec3D &vec) {
	points.push_back(vec);
}

Vec3D PointList::getKeyPoint(int i) {
	return points.at(i);
}

int PointList::getNumFrames() {
	return points.size();
}

} /* namespace std */
