/*
 * Path.h
 *
 *  Created on: 11/09/2013
 *      Author: remnanjona
 */

#ifndef PATH_H_
#define PATH_H_

#include <vector>
#include <chrono>
#include "Spline.h"

namespace std {

class Path: public Spline {
public:
	bool play;
	vector<Vec3D> points;
	chrono::duration<double> time;

	Path();
	virtual ~Path();

	void append(Vec3D);
	void display(chrono::duration<double>, Skeleton *, pose *);
	virtual Vec3D getKeyPoint(int);
	virtual int getNumKeyFrames();
};

} /* namespace std */
#endif /* PATH_H_ */
