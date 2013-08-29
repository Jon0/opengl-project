/*
 * Vec3D.h
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#ifndef VEC3D_H_
#define VEC3D_H_

namespace std {

class Vec3D {

public:
	float x, y, z;
	Vec3D();
	Vec3D(float, float, float);
	virtual ~Vec3D();
	float getX() const;
	float getY() const;
	float getZ() const;
	float dotproduct(Vec3D) const;
	Vec3D crossProduct(Vec3D) const;

	friend Vec3D operator+(const Vec3D&, const Vec3D&);
	friend Vec3D operator-(const Vec3D&, const Vec3D&);
	friend Vec3D operator*(const Vec3D&, const float&);
};

} /* namespace std */
#endif /* VEC3D_H_ */
