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

GVertex::GVertex() {}

GVertex::GVertex( Vec3D d ) {
	position = glm::vec3( d.v[0], d.v[1], d.v[2] );
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
	return position.x;
}

float GVertex::getY() {
	return position.y;
}

float GVertex::getZ() {
	return position.z;
}

glm::vec3 GVertex::getPosition() {
	return position;
}

glm::vec3 GVertex::getNormal() {
	return normal;
}

glm::vec3 GVertex::getTexCoord() {
	return texCoord;
}

void GVertex::setPos(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
}

void GVertex::setNormal(float x, float y, float z) {
	normal.x = x;
	normal.y = y;
	normal.z = z;
}

void GVertex::setTexCoord(float x, float y, float z) {
	texCoord.x = x;
	texCoord.y = y;
	texCoord.z = z;
}

void GVertex::setNormal( float *v ) {
	normal.x = v[0];
	normal.y = v[1];
	normal.z = v[2];
}

void GVertex::setTexCoord( float *v ) {
	texCoord.x = v[0];
	texCoord.y = v[1];
	texCoord.z = v[2];
}

/*
 * ordered by position, texture, normal...
 */
void GVertex::toArray( float *array, int offset) {
	for (int i = 0; i < 3; ++i) {
		array[offset + i + 0] = position[i];
		array[offset + i + 3] = texCoord[i];
		array[offset + i + 6] =  normal[i];
		array[offset + i + 9] = tangent[i];
		array[offset + i + 12] = bitangent[i];
	}
}

void GVertex::print() {
	cout << "( " << position.x << ", " << position.y << ", " << position.z << " )";
}

GVertex::~GVertex() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
