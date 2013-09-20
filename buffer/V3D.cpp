/*
 * V3D.cpp
 *
 *  Created on: 23/04/2013
 *      Author: remnanjona
 */

#include <stdio.h>
#include <iostream>
#include "math.h"
#include "V3D.h"

namespace std {

V3D::V3D( Vec3D d ) {
	e[POS] = d;
}

V3D::V3D(float a, float b, float c) {
	setPos(a, b, c);
}

V3D::V3D(float a, float b, float c, float na, float nb, float nc, float ta, float tb, float tc) {
	setPos(a, b, c);
	setNormal(na, nb, nc);
	setTexCoord(ta, tb, tc);
}

float V3D::getX() {
	return e[POS].v[0];
}

float V3D::getY() {
	return e[POS].v[1];
}

float V3D::getZ() {
	return e[POS].v[2];
}

Vec3D V3D::getPosition() {
	return e[POS];
}

Vec3D V3D::getNormal() {
	return e[NORM];
}

Vec3D V3D::getTexCoord() {
	return e[UV];
}

void V3D::setPos(float x, float y, float z) {
	e[POS].v[0] = x;
	e[POS].v[1] = y;
	e[POS].v[2] = z;
}


void V3D::setNormal(float x, float y, float z) {
	e[NORM].v[0] = x;
	e[NORM].v[1] = y;
	e[NORM].v[2] = z;
}

void V3D::setTexCoord(float x, float y, float z) {
	e[UV].v[0] = x;
	e[UV].v[1] = y;
	e[UV].v[2] = z;
}

void V3D::setNormal( float *v ) {
	e[NORM] = v;
}

void V3D::setTexCoord( float *v ) {
	e[UV] = v;
}

/*
 * ordered by position, normal, texture
 */
void V3D::toArray( float *array, int offset ) {
	for (int i = 0; i < 3; ++i) {
		array[offset + i + 0] = e[POS].v[i];
		array[offset + i + 3] = e[NORM].v[i];
		array[offset + i + 6] = e[UV].v[i];
	}
}

void V3D::print() {
	cout << "( " << e[POS].v[0] << ", " << e[POS].v[1] << ", " << e[POS].v[2] << " )";
}

V3D::~V3D() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
