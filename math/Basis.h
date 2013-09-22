/*
 * Basis.h
 *
 *  Created on: 22/09/2013
 *      Author: remnanjona
 */

#ifndef BASIS_H_
#define BASIS_H_

#include "Vec3D.h"

namespace std {

class GVertex;

class Basis {
public:
	Vec3D v[3];
	Basis();
	Basis(Vec3D a, Vec3D b, Vec3D c);
	virtual ~Basis();

	void normalise();
	void print();

	Basis &operator=(const Basis &);
	Basis &operator+=(const Basis &);
};

Basis textureBasis( GVertex *primary, GVertex *a, GVertex *b );

} /* namespace std */
#endif /* BASIS_H_ */
