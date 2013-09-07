/*
 * Spline.h
 *
 *  Created on: 29/08/2013
 *      Author: remnanjona
 */

#ifndef SPLINE_H_
#define SPLINE_H_

#include "../math/Vec3D.h"

namespace std {

class Spline {
public:
	Vec3D getPoint(float);
	virtual Vec3D getKeyPoint(int) = 0;
	virtual int getNumFrames() = 0;
protected:
	void displayline();
	Vec3D catmull_rom(Vec3D a, Vec3D b, Vec3D c, Vec3D d, float u);
};

} /* namespace std */
#endif /* SPLINE_H_ */
