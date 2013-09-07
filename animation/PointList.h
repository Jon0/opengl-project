/*
 * PointList.h
 *
 *  Created on: 7/09/2013
 *      Author: remnanjona
 */

#ifndef POINTLIST_H_
#define POINTLIST_H_

#include <vector>
#include "../math/Vec3D.h"

namespace std {

class PointList: public Spline {
public:
	PointList();
	virtual ~PointList();
	PointList
	void PointList::append(Vec3D &vec);
	virtual Vec3D getKeyPoint(int);
	virtual int getNumFrames();
protected:
	vector<Vec3D> points;
};

} /* namespace std */
#endif /* POINTLIST_H_ */
