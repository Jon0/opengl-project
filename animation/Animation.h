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
#include "Skeleton.h"
#include "../math/Quaternion.h"

namespace std {

pose *makeState(int);
pose *copyState(int, pose *);

class Animation: public Spline {
public:
	Animation(Skeleton *);
	Animation(int, pose **, Skeleton *);
	virtual ~Animation();

	pose *currentPose();
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
	Vec3D *getCentre();

private:
	pose current;
	Skeleton *skeleton;
	bool show_animate;
	float animate_frame, frame_rate;
	vector<pose> v_pose;
	void setCurrentPose(pose *);
};

} /* namespace std */
#endif /* ANIMATION_H_ */
