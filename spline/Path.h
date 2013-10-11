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

	vector<glm::vec3> points;
	glm::vec3 trans_point, trans_point_n;
	glm::quat rot_point;

	void reset();
	void append(glm::vec3);
	bool getNearestPoint(glm::vec3, int *, float *);
	void translate(float);
	virtual glm::vec3 getKeyPoint(int);
	virtual int getNumKeyFrames();
};

} /* namespace std */
#endif /* PATH_H_ */
