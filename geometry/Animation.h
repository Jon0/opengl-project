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
	Animation(Skeleton *);
	virtual ~Animation();

	pose *currentPose();
	void update(float);
	void addState();
	void setPlaySpeed(int);
	void modSelection(int, float, float, float);
	void animate(bool);
	void setFrame(int);
	int getFrame();
	Vec3D *getCentre();

protected:
	pose *makeState();
	pose *copyState(pose *);

private:
	pose current;
	Skeleton *skeleton;
	bool show_animate;
	float animate_frame, frame_rate;
	vector<pose> v_pose;
};

} /* namespace std */
#endif /* ANIMATION_H_ */
