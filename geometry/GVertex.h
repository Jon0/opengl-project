/*
 * V3D.h
 *
 *  Created on: 23/04/2013
 *      Author: remnanjona
 */

#ifndef V3D_H_
#define V3D_H_

#include <vector>
#include "../math/Basis.h"

#define POS 0
#define NORM 1
#define UV 2

namespace std {

class GVertex {
public:
	Vec3D e[3];
	Basis *basis;

	GVertex();
	GVertex( Vec3D d );
	GVertex(float, float, float);
	GVertex(float, float, float, float, float, float, float, float, float);
	virtual ~GVertex();

	float getX();
	float getY();
	float getZ();

	Vec3D getPosition();
	Vec3D getNormal();
	Vec3D getTexCoord();

	void setPos(float x, float y, float z);
	void setNormal(float x, float y, float z);
	void setTexCoord(float x, float y, float z);

	void setNormal( float * );
	void setTexCoord( float * );

	void toArray( float *array, int offset );
	void print();
};

typedef vector<GVertex> GPolygon;

} /* namespace std */
#endif /* V3D_H_ */
