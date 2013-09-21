/*
 * Basis.cpp
 *
 *  Created on: 22/09/2013
 *      Author: remnanjona
 */

#include "../geometry/GVertex.h"
#include "Basis.h"

namespace std {

Basis::Basis() {}

Basis::Basis(Vec3D a, Vec3D b, Vec3D c) {
	v[0] = a;
	v[1] = b;
	v[2] = c;
}

Basis::~Basis() {
	// TODO Auto-generated destructor stub
}

Basis textureBasis( GVertex *primary, GVertex *a, GVertex *b ) {
	Basis basis;
	Vec3D deltaPos1 = a->getPosition() - primary->getPosition();
	Vec3D deltaPos2 = b->getPosition() - primary->getPosition();
	Vec3D deltaUV1 = a->getTexCoord() - primary->getTexCoord();
	Vec3D deltaUV2 = b->getTexCoord() - primary->getTexCoord();
	float r = 1.0f / (deltaUV1.getX() * deltaUV2.getY() - deltaUV1.getY() * deltaUV2.getX());

	/*
	 * tangent
	 */
	basis.v[0] = (deltaPos1 * deltaUV2.getY()   - deltaPos2 * deltaUV1.getY())*r;


	/*
	 * bitangent
	 */
	basis.v[1] = (deltaPos2 * deltaUV1.getX()   - deltaPos1 * deltaUV2.getX())*r;

	/*
	 * normal
	 */
	basis.v[2] = basis.v[0].crossProduct( basis.v[1] );

	return basis;
}


} /* namespace std */
