/*
 * Quaternion.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <stdio.h>
#include <math.h>

#include "Vec3D.h"
#include "Quaternion.h"

namespace std {

float rad_to_deg = 360.0/(2 * M_PI);

Quaternion::Quaternion(float r, float i, float j, float k) :
		w(r), x(i), y(j), z(k) {
}

Quaternion::Quaternion(float angle, const Vec3D &p) {
	float ang = angle / (2 * 57.2957795); //convert into radians and halve
	w = cos(ang);
	float s = sin(ang);
	x = s * p.getX();
	y = s * p.getY();
	z = s * p.getZ();
}

//Out by a factor of 2  like in the arc ball paper
Quaternion::Quaternion(const Vec3D &p1, const Vec3D &p2) {
	w = p1.dotproduct(p2);
	Vec3D cross = p1.crossProduct(p2);
	x = cross.getX();
	y = cross.getY();
	z = cross.getZ();
}

Quaternion::Quaternion(float mat[16]) {
	float tr, s, q[4];
	int i, j, k;
	int nxt[3] = { 1, 2, 0 };
	tr = mat[0] + mat[5] + mat[10];
	if (tr > 0.0) {
		s = sqrt(tr + 1.0);
		w = s / 2.0;
		s = 0.5 / s;
		x = (mat[4 + 2] - mat[2 * 4 + 1]) * s;
		y = (mat[4 * 2 + 0] - mat[2]) * s;
		z = (mat[1] - mat[4]) * s;
	} else {
		i = 0;
		if (mat[5] > mat[0]) {
			i = 1;
		}
		if (mat[10] > mat[4 * i + i]) {
			i = 2;
		}
		j = nxt[i];
		k = nxt[j];
		s = sqrt((mat[4 * i + i] - (mat[4 * j + i] + mat[4 * k + k])) + 1.0);
		q[i] = s * 0.5;
		if (s != 0.0) {
			s = 0.5 / s;
			q[3] = (mat[4 * j + k] - mat[4 * k + j]) * s;
			q[j] = (mat[4 * i + j] - mat[4 * j + i]) * s;
			q[k] = (mat[4 * i + k] - mat[4 * k + i]) * s;
			x = q[0];
			y = q[1];
			z = q[2];
			w = q[3];
		}
	}
}

Quaternion::Quaternion(const Quaternion &q) :
	w(q.w), x(q.x), y(q.y), z(q.z) {
}

Quaternion::Quaternion(Quaternion &&q) :
		w(q.w), x(q.x), y(q.y), z(q.z) {
}

Quaternion::~Quaternion() {

}

Vec3D Quaternion::vector() const{
	Vec3D v;
	v.v[0] = x;
	v.v[1] = y;
	v.v[2] = z;
	return v;
}

float Quaternion::firstValue() const{
	return w;
}

float Quaternion::length() const {
	float l = w * w + x * x + y * y + z * z;
	l = sqrt(l);
	return l;
}

Quaternion Quaternion::conjugate() const {
	Quaternion q(w, -x, -y, -z);
	return q;
}

Quaternion Quaternion::multiplicativeInverse() const {
	float len = length();
	len = len * len;
	Quaternion c = conjugate();
	Quaternion inverse = c / len;
	return inverse;
}

Quaternion Quaternion::normalise() const {
	float l = length();
	return (*this) / l;
}

void Quaternion::print() const {
	printf("(%.2f,%.2f.%.2f,%.2f)",w,x,y,z);
}

void Quaternion::toMatrix(float* matrix) const {
	//OpenGL friendly => by column!
	Quaternion q = normalise();

	//column 1
	matrix[0] = q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z;
	matrix[1] = 2 * q.x * q.y + 2 * q.w * q.z;
	matrix[2] = 2 * q.x * q.z - 2 * q.w * q.y;
	matrix[3] = 0;

	//column 2
	matrix[4] = 2 * q.x * q.y - 2 * q.w * q.z;
	matrix[5] = q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z;
	matrix[6] = 2 * q.y * q.z + 2 * q.w * q.x;
	matrix[7] = 0;

	//column 3
	matrix[8] = 2 * q.x * q.z + 2 * q.w * q.y;
	matrix[9] = 2 * q.y * q.z - 2 * q.w * q.x;
	matrix[10] = q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z;
	matrix[11] = 0;

	//column 4
	matrix[12] = 0;
	matrix[13] = 0;
	matrix[14] = 0;
	matrix[15] = q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z;
}

Quaternion& Quaternion::operator=(const Quaternion& q) {
	w = q.w;
	x = q.x;
	y = q.y;
	z = q.z;
	return *this;
}

void Quaternion::rotate(Quaternion &other) {
	Quaternion new_q = other * *this;
	w = new_q.w;
	x = new_q.x;
	y = new_q.y;
	z = new_q.z;
}

void Quaternion::rotateb(Quaternion &other) {
	Quaternion new_q = *this * other;
	w = new_q.w;
	x = new_q.x;
	y = new_q.y;
	z = new_q.z;
}

Quaternion operator+(const Quaternion& q1, const Quaternion& q2) {
	Quaternion q(q1.w + q2.w, q1.x + q2.x, q1.y + q2.y, q1.z + q2.z);
	return q;
}

Quaternion operator-(const Quaternion& q1, const Quaternion& q2) {
	Quaternion q(q1.w - q2.w, q1.x - q2.x, q1.y - q2.y, q1.z - q2.z);
	return q;
}

Quaternion operator*(const Quaternion& q1, const Quaternion& q2) {
	float a = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	float b = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	float c = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	float d = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;

	Quaternion q(a, b, c, d);
	return q;
}

Quaternion operator*(const Quaternion& q1, const float& f) {
	Quaternion q(f * q1.w, f * q1.x, f * q1.y, f * q1.z);
	return q;
}

Quaternion operator/(const Quaternion& q1, const Quaternion& q2) {
	Quaternion q2inv = q2.multiplicativeInverse();
	Quaternion r = q1 * q2inv;
	return r;
}

Quaternion operator/(const Quaternion& q1, const float& f) {
	Quaternion q(q1.w / f, q1.x / f, q1.y / f, q1.z / f);
	return q;
}

float dotproduct(const Quaternion& q1, const Quaternion& q2) {
	float f = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
	return f;
}

Quaternion slerp(const Quaternion& p1, const Quaternion& q1, float t) {
	Quaternion q = q1.normalise();
	Quaternion p = p1.normalise();
	float epsilon = 0.0001;
	if (dotproduct(p, q) < 0) {
		q = q * -1;
	}
	float dpq = dotproduct(p, q);
	if ((1.0 - dpq) > epsilon) {
		float w = acos(dpq);
		return ((sin((1 - t) * w) * p) + (sin(t * w) * q)) / sin(w);
	} else {
		return (1 - t) * p + t * q;
	}
}

/* convert angles in degrees to quaternion */
Quaternion *fromEular(float x, float y, float z) {
	double m = 0.0174532925 / 2.0;
	return new Quaternion(cos(x*m)*cos(y*m)*cos(z*m) + sin(x*m)*sin(y*m)*sin(z*m),
				sin(x*m)*cos(y*m)*cos(z*m) - cos(x*m)*sin(y*m)*sin(z*m),
				cos(x*m)*sin(y*m)*cos(z*m) + sin(x*m)*cos(y*m)*sin(z*m),
				cos(x*m)*cos(y*m)*sin(z*m) - sin(x*m)*sin(y*m)*cos(z*m));
}

} /* namespace std */
