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

	void update(float);
	void addFrame();
	void insertFrame();
	void setPlaySpeed(int);
	void rollSelection(int, float);
	void modSelection(int, float, float, float);
	void modSelection(int id, Quaternion &q);
	void animate(bool);
	void setFrame(int);
	int getFrame();

private:
	Skeleton *skeleton;
	bool show_animate;
	float animate_frame, frame_rate;
	vector<pose> v_pose;
};

} /* namespace std */
#endif /* ANIMATION_H_ */
