/*
 * AnimationPlayer.h
 *
 *  Created on: 15/09/2013
 *      Author: remnanjona
 */

#ifndef ANIMATIONPLAYER_H_
#define ANIMATIONPLAYER_H_

#include <memory>
#include <string>
#include <vector>

#include "../SpeedCurve.h"
#include "../../spline/Path.h"
#include "../../spline/DynamicPose.h"
#include "../../load/AnimationLoader.h"

namespace std {

class SkeletonTransform {
public:
	SkeletonTransform(shared_ptr<Skeleton>);
	SkeletonTransform(shared_ptr<Skeleton>, string);
	virtual ~SkeletonTransform();
	void set_time(float);
	void apply_transform();
	void set_pose_seq(int);
	void set_edit(bool);
	void reset();
	void loadFile(string);
	void saveFile(string);
	void addFile(string);
	bool edit;
	int pose_seq;
	float path_offset;
	SpeedCurve speed_curve;
	pose current_pose;
	shared_ptr<Skeleton> skeleton;
	shared_ptr<Path> path;
	shared_ptr<AnimationLoader> aloader;
	vector<DynamicPose> animation;


};

} /* namespace std */
#endif /* ANIMATIONPLAYER_H_ */
