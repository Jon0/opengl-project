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
	virtual ~Spline() {};
	Vec3D getPoint(float);
	Vec3D getDistPoint(float);
	float getPointInc(float, float);
	float calcPointInc(float, float);
	void equalise();
	virtual Vec3D getKeyPoint(int) = 0;
	virtual int getNumFrames() = 0;
protected:
	float delta, segments, spline_length;
	vector<float> u_delta;
	void displayline(float a, float b);
	Vec3D catmull_rom(Vec3D a, Vec3D b, Vec3D c, Vec3D d, float u);
};

} /* namespace std */
#endif /* SPLINE_H_ */
