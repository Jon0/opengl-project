/*
 * Animation.h
 *
 *  Created on: 30/08/2013
 *      Author: remnanjona
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <vector>
#include "Spline.h"
#include "../geometry/Skeleton.h"
#include "../math/Quaternion.h"

namespace std {

class Animation {
public:
	Animation(Skeleton *);
	Animation(int, pose **, Skeleton *);
	virtual ~Animation();

	void update(float, pose *);
	void addFrame();
	void insertFrame(float);
	void rollSelection(int, float);
	void modSelection(int, int, float, float, float);
	void modSelection(int, int id, Quaternion &q);

private:
	int numBones;
	vector<pose> v_pose;
};

} /* namespace std */
#endif /* ANIMATION_H_ */
