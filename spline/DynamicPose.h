/*
 * Animation.h
 *
 *  Created on: 30/08/2013
 *      Author: remnanjona
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <memory>
#include <vector>
#include "Spline.h"
#include "../geometry/Skeleton.h"
#include "../math/Quaternion.h"

namespace std {

class DynamicPose {
public:
	DynamicPose(shared_ptr<Skeleton>);
	DynamicPose(int, pose **, shared_ptr<Skeleton>);
	virtual ~DynamicPose();

	void update(float, pose *);
	void addFrame();
	void addFrame( pose newPose );
	void insertFrame(float);
	void rollSelection(int, float);
	void modSelection(int, int, float, float, float);
	void modSelection(int, int id, const glm::quat &q);
	void setPathLength(float);
	int numFrames();

private:
	float path_length; // the length of arc the pose should run over
	int numBones;
	vector<pose> v_pose;
};

} /* namespace std */
#endif /* ANIMATION_H_ */
