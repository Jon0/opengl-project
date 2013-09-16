/*
 * Path.cpp
 *
 *  Created on: 11/09/2013
 *      Author: remnanjona
 */

#include <iostream>
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
		rot_point(1.0, 0.0, 0.0, 0.0),
		test(false) {}

Path::~Path() {}

void Path::append(Vec3D point) {
	points.push_back(point);
	equaliseLength();
}

bool Path::getNearestPoint(Vec3D vec, int *index, float *dist) {
	for (unsigned int i = 0; i < points.size(); ++i) {
		float newd = ((Vec3D)points.front()).getDistance(vec);
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
		Vec3D newpoint =  getDistPoint(distance);

		Vec3D v1 = (newpoint - trans_point).normalise();
		Vec3D v2 = (trans_point - trans_point_n).normalise();

		if (v1.length() > 0 && v2.length() > 0) {

			//cout << v1.v[0] << ", " << v1.v[1] << ", " << v1.v[2] << endl;
			//cout << v2.v[0] << ", " << v2.v[1] << ", " << v2.v[2] << endl;

			Quaternion k =
					Quaternion(0, v1.v[0], v1.v[1], v1.v[2])
							* Quaternion(0, v2.v[0], v2.v[1], v2.v[2]).multiplicativeInverse();

			rot_point.rotate(k);

		}
		trans_point_n = trans_point;
		trans_point = newpoint;
	}

	glTranslatef(trans_point.getX(), trans_point.getY(), trans_point.getZ());
	GLfloat mat[16];
	rot_point.toMatrix(mat);
	glMultMatrixf(mat);
}

Vec3D Path::getKeyPoint(int i) {
	return points.at(i + 1);
}

int Path::getNumKeyFrames() {
	return points.size() - 2;
}

} /* namespace std */
