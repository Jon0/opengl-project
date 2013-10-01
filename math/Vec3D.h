/*
 * Vec3D.h
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#ifndef VEC3D_H_
#define VEC3D_H_

namespace std {

class Quaternion;

class Vec3D {
public:
	float v[3];
	Vec3D();
	Vec3D(float *);
	Vec3D(float, float, float);
	virtual ~Vec3D();

	float getDistance(const Vec3D&) const;
	float getDistanceSq(const Vec3D &) const;
	float getX() const;
	float getY() const;
	float getZ() const;
	float dotproduct(Vec3D) const;
	Vec3D crossProduct(Vec3D) const;
	float length() const;
	void setLength(float);
	void interpolate(Vec3D other, float percent);
	Vec3D normalise() const;
	bool similiar(Vec3D &other);

	Vec3D &operator=(const float *vec);
	Vec3D &operator=(const Vec3D &);
	friend Vec3D operator+(const Vec3D&, const Vec3D&);
	friend Vec3D operator-(const Vec3D&, const Vec3D&);
	friend Vec3D operator*(const Vec3D&, const float&);
	friend Vec3D operator*(const Quaternion&, const Vec3D&);
	friend Vec3D operator/(const Vec3D&, const float&);
};

} /* namespace std */
#endif /* VEC3D_H_ */
