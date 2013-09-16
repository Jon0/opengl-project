/*
 * Path.h
 *
 *  Created on: 11/09/2013
 *      Author: remnanjona
 */

#ifndef PATH_H_
#define PATH_H_

#include <memory>
#include <vector>
#include <chrono>
#include "../geometry/Skeleton.h"
#include "Spline.h"

namespace std {

class Path: public Spline {
public:
	Path();
	virtual ~Path();

	vector<Vec3D> points;
	Vec3D trans_point, trans_point_n;
	Quaternion rot_point;

	void reset();
	void append(Vec3D);
	bool getNearestPoint(Vec3D, int *, float *);
	void translate(float);
	virtual Vec3D getKeyPoint(int);
	virtual int getNumKeyFrames();
};

} /* namespace std */
#endif /* PATH_H_ */
