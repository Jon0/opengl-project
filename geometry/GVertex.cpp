/*
 * V3D.cpp
 *
 *  Created on: 23/04/2013
 *      Author: remnanjona
 */

#include <stdio.h>
#include <iostream>
#include "math.h"
#include "GVertex.h"

namespace std {

GVertex::GVertex(): e(), basis() {
}

GVertex::GVertex( Vec3D d ) {
	e[POS] = d;
}

GVertex::GVertex(float a, float b, float c) {
	setPos(a, b, c);
}

GVertex::GVertex(float a, float b, float c, float na, float nb, float nc, float ta, float tb, float tc) {
	setPos(a, b, c);
	setNormal(na, nb, nc);
	setTexCoord(ta, tb, tc);
}

float GVertex::getX() {
	return e[POS].v[0];
}

float GVertex::getY() {
	return e[POS].v[1];
}

float GVertex::getZ() {
	return e[POS].v[2];
}

Vec3D GVertex::getPosition() {
	return e[POS];
}

Vec3D GVertex::getNormal() {
	return e[NORM];
}

Vec3D GVertex::getTexCoord() {
	return e[UV];
}

void GVertex::setPos(float x, float y, float z) {
	e[POS].v[0] = x;
	e[POS].v[1] = y;
	e[POS].v[2] = z;
}


void GVertex::setNormal(float x, float y, float z) {
	e[NORM].v[0] = x;
	e[NORM].v[1] = y;
	e[NORM].v[2] = z;
}

void GVertex::setTexCoord(float x, float y, float z) {
	e[UV].v[0] = x;
	e[UV].v[1] = y;
	e[UV].v[2] = z;
}

void GVertex::setNormal( float *v ) {
	e[NORM] = v;
}

void GVertex::setTexCoord( float *v ) {
	e[UV] = v;
}

/*
 * ordered by position, normal, texture
 */
void GVertex::toArray( float *array, int offset ) {
	for (int i = 0; i < 3; ++i) {
		array[offset + i + 0] = e[POS].v[i];
		array[offset + i + 3] = e[NORM].v[i];
		array[offset + i + 6] = e[UV].v[i];
	}
}

void GVertex::print() {
	cout << "( " << e[POS].v[0] << ", " << e[POS].v[1] << ", " << e[POS].v[2] << " )";
}

GVertex::~GVertex() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
