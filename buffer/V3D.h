/*
 * V3D.h
 *
 *  Created on: 23/04/2013
 *      Author: remnanjona
 */

#ifndef V3D_H_
#define V3D_H_

#include "../math/Vec3D.h"

#define POS 0
#define NORM 1
#define UV 2

namespace std {

class V3D {
public:
	Vec3D e[3];

	V3D( Vec3D d );
	V3D(float, float, float);
	V3D(float, float, float, float, float, float, float, float, float);

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

	void add(V3D *other);
	void sub(V3D *other);
	float length();

	/**
	 * modifies the length, but maintains the direction
	 */
	void setLength(float);

	float distance(V3D *);

	void interpolate(V3D *other, float percent);

	float dot( V3D *other);
	float dot( float, float, float );
	float *cross( float * );

	void toArray( float *array, int offset );
	void print();
	virtual ~V3D();
};

} /* namespace std */
#endif /* V3D_H_ */
