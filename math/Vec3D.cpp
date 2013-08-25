/*
 * Vec3D.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include "Vec3D.h"

namespace std {

Vec3D::Vec3D() {
	x = y = z = 0;
}

Vec3D::Vec3D(float a, float b, float c) {
	x = a;
	y = b;
	z = c;
}

float Vec3D::getX() const {
	return x;
}

float Vec3D::getY() const {
	return y;
}

float Vec3D::getZ() const {
	return z;
}

float Vec3D::dotproduct(Vec3D q) const {
	float a = 0;
	a += x * q.x;
	a += y * q.y;
	a += z * q.z;
	return a;
}

Vec3D Vec3D::crossProduct(Vec3D q) const {
	Vec3D cross;
	cross.x = y * q.z - z * q.y;
	cross.y = z * q.x - x * q.z;
	cross.z = x * q.y - y * q.x;
	return cross;
}

Vec3D::~Vec3D() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
