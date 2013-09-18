/*
 * PointArray.h
 *
 *  Created on: 18/09/2013
 *      Author: remnanjona
 */

#ifndef POINTARRAY_H_
#define POINTARRAY_H_

#include <vector>
#include <math.h>

namespace std {

template<class T>
class PointArray {
public:
	vector<T> point;
	const float segments;


	PointArray(float s):
		point(),
		segments(s) {}

	virtual ~PointArray() {}

	T getPoint(float dist) {

		float mod = fmod(dist, segments);
		float percent = mod / segments;
		int seg_a = (int) ((dist - mod) / segments) % (point.size() - 1);
		return point.at(seg_a) * (1 - percent) + point.at(seg_a + 1) * percent;

	}
};

template class PointArray<float>;

} /* namespace std */
#endif /* POINTARRAY_H_ */
