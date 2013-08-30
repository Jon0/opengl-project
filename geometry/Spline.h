/*
 * Spline.h
 *
 *  Created on: 29/08/2013
 *      Author: remnanjona
 */

#ifndef SPLINE_H_
#define SPLINE_H_

#include <vector>
#include "../math/Vec3D.h"

namespace std {

class Spline {
public:
	Spline();
	virtual ~Spline();
	void append(Vec3D &);
	void display();
	Vec3D getPoint(float);
protected:
	vector<Vec3D> points;
	void displayline(Vec3D a, Vec3D b, Vec3D c, Vec3D d);
	Vec3D catmull_rom(Vec3D a, Vec3D b, Vec3D c, Vec3D d, float u);
};

} /* namespace std */
#endif /* SPLINE_H_ */
