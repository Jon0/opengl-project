/*
 * Vec3D.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <math.h>
#include "Vec3D.h"

namespace std {

Vec3D::Vec3D(): v() {}

Vec3D::Vec3D(float *f) {
	v[0] = f[0];
	v[1] = f[1];
	v[2] = f[2];
}

Vec3D::Vec3D(float x, float y, float z) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

Vec3D::~Vec3D() {
	// TODO Auto-generated destructor stub
}

float Vec3D::getDistance(const Vec3D &other) const {
	float dx = other.v[0] - v[0], dy = other.v[1] - v[1], dz = other.v[2] - v[2];
	return sqrt(dx*dx + dy*dy + dz*dz);
}

float Vec3D::getDistanceSq(const Vec3D &other) const {
	float dx = other.v[0] - v[0], dy = other.v[1] - v[1], dz = other.v[2] - v[2];
	return dx*dx + dy*dy + dz*dz;
}

float Vec3D::getX() const {
	return v[0];
}

float Vec3D::getY() const {
	return v[1];
}

float Vec3D::getZ() const {
	return v[2];
}

float Vec3D::dotproduct(Vec3D q) const {
	float a = 0;
	a += v[0] * q.v[0];
	a += v[1] * q.v[1];
	a += v[2] * q.v[2];
	return a;
}

Vec3D Vec3D::crossProduct(Vec3D q) const {
	Vec3D cross;
	cross.v[0] = v[1] * q.v[2] - v[2] * q.v[1];
	cross.v[1] = v[2] * q.v[0] - v[0] * q.v[2];
	cross.v[2] = v[0] * q.v[1] - v[1] * q.v[0];
	return cross;
}

Vec3D operator+(const Vec3D &a, const Vec3D &b) {
	Vec3D p(a.v[0]+b.v[0], a.v[1]+b.v[1], a.v[2]+b.v[2]);
	return p;
}

Vec3D operator-(const Vec3D &a, const Vec3D &b) {
	Vec3D p(a.v[0]-b.v[0], a.v[1]-b.v[1], a.v[2]-b.v[2]);
	return p;
}

Vec3D operator*(const Vec3D &a, const float &f) {
	Vec3D p(a.v[0]*f, a.v[1]*f, a.v[2]*f);
	return p;
}

Vec3D operator/(const Vec3D &a, const float &f) {
	Vec3D p(a.v[0]/f, a.v[1]/f, a.v[2]/f);
	return p;
}

} /* namespace std */
