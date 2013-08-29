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
protected:
	vector<Vec3D> points;
};

} /* namespace std */
#endif /* SPLINE_H_ */
