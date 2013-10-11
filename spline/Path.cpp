/*
 * Path.cpp
 *
 *  Created on: 11/09/2013
 *      Author: remnanjona
 */

#include <math.h>
#include <GL/glut.h>
#include "../geometry/Skeleton.h"
#include "Path.h"

namespace std {

Path::Path():
		Spline(),
		points(),
		trans_point(0.0, 0.0, 0.0),
		trans_point_n(0.0, 0.0, 0.0),
		rot_point(1.0, 0.0, 0.0, 0.0) {}

Path::~Path() {}

void Path::reset() {
	trans_point = glm::vec3(0.0, 0.0, 0.0);
	trans_point_n = glm::vec3(0.0, 0.0, 0.0);
	rot_point = glm::quat(1.0, 0.0, 0.0, 0.0);
	points.clear();
	spline_length = 0.0;
	distance.point.clear();
}

void Path::append(glm::vec3 point) {
	points.push_back(point);
	equaliseLength();
}

bool Path::getNearestPoint(glm::vec3 vec, int *index, float *dist) {
	for (unsigned int i = 0; i < points.size(); ++i) {

		float newd = glm::distance( (glm::vec3)points.front(), vec );
		if (newd < *dist) {
			*dist = newd;
			*index = i;
			return true;
		}
	}
	return false;
}

void Path::translate(float distance) {
	if (getNumKeyFrames() >= 2) {
		glm::vec3 newpoint =  getDistPoint(distance);
		glm::vec3 v1 = glm::normalize( newpoint - trans_point );
		glm::vec3 v2 = glm::normalize( trans_point - trans_point_n );
		if (v1.length() > 0 && v2.length() > 0) {
			glm::quat k = glm::quat(0, v1.x, v1.y, v1.z) * glm::inverse( glm::quat(0, v2.x, v2.y, v2.z) );
			glm::quat s = glm::slerp(glm::quat(1,0,0,0), k, 0.5f);
			rot_point = s * rot_point;
		}
		trans_point_n = trans_point;
		trans_point = newpoint;
	}

	glTranslatef(trans_point.x, trans_point.y, trans_point.z);
	glMultMatrixf( &glm::mat4_cast(rot_point)[0][0] );
}

glm::vec3 Path::getKeyPoint(int i) {
	return points.at(i + 1);
}

int Path::getNumKeyFrames() {
	return points.size() - 2;
}

} /* namespace std */
