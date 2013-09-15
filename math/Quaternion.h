/*
 * Quaternion.h
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#ifndef QUATERNION_H_
#define QUATERNION_H_

namespace std {

extern float rad_to_deg;

class Vec3D;

class Quaternion {
private:
	float w, x, y, z;

public:
	Quaternion(const Vec3D &, const Vec3D &);
	Quaternion(float, const Vec3D &);
	Quaternion(float = 0, float = 0, float = 0, float = 0);
	Quaternion(float[16]);
	Quaternion(const Quaternion &);
	Quaternion(Quaternion &&);
	~Quaternion();
	Quaternion& operator=(const Quaternion &);
	float length() const;
	Quaternion conjugate() const;
	void toMatrix(float*) const;
	Quaternion normalise() const;
	Quaternion multiplicativeInverse() const;
	Vec3D vector() const;
	float firstValue() const;
	void print() const;
	void rotate(Quaternion &);
	void rotateb(Quaternion &);

	friend Quaternion operator+(const Quaternion&, const Quaternion&);
	friend Quaternion operator-(const Quaternion&, const Quaternion&);
	friend Quaternion operator*(const Quaternion&, const Quaternion&);
	friend Quaternion operator*(const Quaternion&, const float&);
	friend Quaternion operator/(const Quaternion&, const Quaternion&);
	friend Quaternion operator/(const Quaternion&, const float&);
	friend float dotproduct(const Quaternion&, const Quaternion&);
	friend Quaternion slerp(const Quaternion&, const Quaternion&, float);
};

Quaternion *fromEular(float, float, float);

} /* namespace std */
#endif /* QUATERNION_H_ */
