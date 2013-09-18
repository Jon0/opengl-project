/*
 * Spline.h
 *
 *  Created on: 29/08/2013
 *      Author: remnanjona
 */

#ifndef SPLINE_H_
#define SPLINE_H_

#include <vector>
#include "../math/PointArray.h"
#include "../math/Vec3D.h"

namespace std {

class Spline {
public:
	Spline();
	virtual ~Spline() {};
	float getULength();
	float getArcLength();
	Vec3D getPoint(float);
	Vec3D getDistPoint(float);
	float calcPointInc(float, float);
	void displayline();
	void equaliseLength();
	virtual Vec3D getKeyPoint(int) = 0;
	virtual int getNumKeyFrames() = 0;

protected:
	Vec3D catmull_rom(Vec3D a, Vec3D b, Vec3D c, Vec3D d, float u);
	float spline_length;
	PointArray<float> distance;
};

} /* namespace std */
#endif /* SPLINE_H_ */
