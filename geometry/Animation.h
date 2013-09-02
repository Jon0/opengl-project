/*
 * Animation.h
 *
 *  Created on: 30/08/2013
 *      Author: remnanjona
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <vector>
#include "Skeleton.h"
#include "../math/Quaternion.h"

namespace std {

class Animation {
public:
	Animation();
	virtual ~Animation();

	void display();
private:
	vector<pose> v_pose;
};

} /* namespace std */
#endif /* ANIMATION_H_ */
