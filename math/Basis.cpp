/*
 * Basis.cpp
 *
 *  Created on: 22/09/2013
 *      Author: remnanjona
 */

#include <iostream>
#include "../geometry/GVertex.h"
#include "Basis.h"

namespace std {

Basis::Basis(): v() {}

Basis::Basis(Vec3D a, Vec3D b, Vec3D c) {
	v[0] = a;
	v[1] = b;
	v[2] = c;
}

Basis::~Basis() {
	// TODO Auto-generated destructor stub
}

void Basis::normalise() {
	v[0] = v[0].normalise();
	v[1] = v[1].normalise();
	v[2] = v[2].normalise();
}

void Basis::print() {
	cout << "[0] " << v[0].v[0] << ", " << v[0].v[1] << ", " << v[0].v[2] << endl;
	cout << "[1] " << v[1].v[0] << ", " << v[1].v[1] << ", " << v[1].v[2] << endl;
	cout << "[2] " << v[2].v[0] << ", " << v[2].v[1] << ", " << v[2].v[2] << endl;
}

Basis &Basis::operator=(const Basis &b) {
	v[0] = b.v[0];
	v[1] = b.v[1];
	v[2] = b.v[2];
	return *this;
}

Basis &Basis::operator+=(const Basis &b) {
	v[0] = v[0] + b.v[0];
	v[1] = v[1] + b.v[1];
	v[2] = v[2] + b.v[2];
	return *this;
}

/*
 * maybe remove this later
 */
Basis textureBasis( GVertex *primary, GVertex *a, GVertex *b ) {
	Basis basis;
	glm::vec3 deltaPos1 = a->getPosition() - primary->getPosition();
	glm::vec3 deltaPos2 = b->getPosition() - primary->getPosition();
	glm::vec3 deltaUV1 = a->getTexCoord() - primary->getTexCoord();
	glm::vec3 deltaUV2 = b->getTexCoord() - primary->getTexCoord();

	float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
	glm::vec3 norm = glm::normalize( glm::cross(deltaPos1,deltaPos2) );



	/*
	 * tangent
	 */
	//basis.v[0] = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
	//basis.v[0].normalise();

	/*
	 * bitangent
	 */
	//basis.v[1] = norm.crossProduct( basis.v[0] );

	/*
	 * normal
	 */
	//basis.v[2] = norm;

	return basis;
}


} /* namespace std */
