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

Quaternion::Quaternion(float r, float i, float j, float k) :
		a(r), b(i), c(j), d(k) {
}

Quaternion::Quaternion(float angle, const Vec3D &p) {
	float ang = angle / (2 * 57.2957795); //convert into radians and halve
	a = cos(ang);
	float s = sin(ang);
	b = s * p.getX();
	c = s * p.getY();
	d = s * p.getZ();
}

//Out by a factor of 2  like in the arc ball paper
Quaternion::Quaternion(const Vec3D &p1, const Vec3D &p2) {
	a = p1.dotproduct(p2);
	Vec3D cross = p1.crossProduct(p2);
	b = cross.x;
	c = cross.y;
	d = cross.z;
}

Quaternion::Quaternion(float mat[16]) {
	float tr, s, q[4];
	int i, j, k;
	int nxt[3] = { 1, 2, 0 };
	tr = mat[0] + mat[5] + mat[10];
	if (tr > 0.0) {
		s = sqrt(tr + 1.0);
		a = s / 2.0;
		s = 0.5 / s;
		b = (mat[4 + 2] - mat[2 * 4 + 1]) * s;
		c = (mat[4 * 2 + 0] - mat[2]) * s;
		d = (mat[1] - mat[4]) * s;
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
			b = q[0];
			c = q[1];
			d = q[2];
			a = q[3];
		}
	}
}

Quaternion::Quaternion(const Quaternion& q) :
		a(q.a), b(q.b), c(q.c), d(q.d) {

}

Quaternion::~Quaternion() {

}

Vec3D Quaternion::vector() const{
	Vec3D v;
	v.x = b;
	v.y = c;
	v.z = d;
	return v;
}

float Quaternion::firstValue() const{
	return a;
}

float Quaternion::length() const {
	float l = a * a + b * b + c * c + d * d;
	l = sqrt(l);
	return l;
}

Quaternion Quaternion::conjugate() const {
	Quaternion q(a, -b, -c, -d);
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
	printf("(%.2f,%.2f.%.2f,%.2f)",a,b,c,d);
}

void Quaternion::toMatrix(float* matrix) const {
	//OpenGL friendly => by column!
	Quaternion q = normalise();

	//column 1
	matrix[0] = q.a * q.a + q.b * q.b - q.c * q.c - q.d * q.d;
	matrix[1] = 2 * q.b * q.c + 2 * q.a * q.d;
	matrix[2] = 2 * q.b * q.d - 2 * q.a * q.c;
	matrix[3] = 0;

	//column 2
	matrix[4] = 2 * q.b * q.c - 2 * q.a * q.d;
	matrix[5] = q.a * q.a - q.b * q.b + q.c * q.c - q.d * q.d;
	matrix[6] = 2 * q.c * q.d + 2 * q.a * q.b;
	matrix[7] = 0;

	//column 3
	matrix[8] = 2 * q.b * q.d + 2 * q.a * q.c;
	matrix[9] = 2 * q.c * q.d - 2 * q.a * q.b;
	matrix[10] = q.a * q.a - q.b * q.b - q.c * q.c + q.d * q.d;
	matrix[11] = 0;

	//column 4
	matrix[12] = 0;
	matrix[13] = 0;
	matrix[14] = 0;
	matrix[15] = q.a * q.a + q.b * q.b + q.c * q.c + q.d * q.d;
}

Quaternion& Quaternion::operator=(const Quaternion& q) {
	a = q.a;
	b = q.b;
	c = q.c;
	d = q.d;
	return *this;
}

void Quaternion::rotate(Quaternion &other) {
	Quaternion new_q = other * *this;
	a = new_q.a;
	b = new_q.b;
	c = new_q.c;
	d = new_q.d;
}

Quaternion operator+(const Quaternion& q1, const Quaternion& q2) {
	Quaternion q(q1.a + q2.a, q1.b + q2.b, q1.c + q2.c, q1.d + q2.d);
	return q;
}

Quaternion operator-(const Quaternion& q1, const Quaternion& q2) {
	Quaternion q(q1.a - q2.a, q1.b - q2.b, q1.c - q2.c, q1.d - q2.d);
	return q;
}

Quaternion operator*(const Quaternion& q1, const Quaternion& q2) {
	float a = q1.a * q2.a - q1.b * q2.b - q1.c * q2.c - q1.d * q2.d;
	float b = q1.a * q2.b + q1.b * q2.a + q1.c * q2.d - q1.d * q2.c;
	float c = q1.a * q2.c - q1.b * q2.d + q1.c * q2.a + q1.d * q2.b;
	float d = q1.a * q2.d + q1.b * q2.c - q1.c * q2.b + q1.d * q2.a;

	Quaternion q(a, b, c, d);
	return q;
}

Quaternion operator*(const Quaternion& q1, const float& f) {
	Quaternion q(f * q1.a, f * q1.b, f * q1.c, f * q1.d);
	return q;
}

Quaternion operator/(const Quaternion& q1, const Quaternion& q2) {
	Quaternion q2inv = q2.multiplicativeInverse();
	Quaternion r = q1 * q2inv;
	return r;
}

Quaternion operator/(const Quaternion& q1, const float& f) {
	Quaternion q(q1.a / f, q1.b / f, q1.c / f, q1.d / f);
	return q;
}

float dotproduct(const Quaternion& q1, const Quaternion& q2) {
	float f = q1.a * q2.a + q1.b * q2.b + q1.c * q2.c + q1.d * q2.d;
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

} /* namespace std */
