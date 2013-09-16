/*
 * AnimationPlayer.cpp
 *
 *  Created on: 15/09/2013
 *      Author: remnanjona
 */

#include "SkeletonTransform.h"

namespace std {

SkeletonTransform::SkeletonTransform(shared_ptr<Skeleton> skeleton):
		speed_curve{},
		skeleton{skeleton},
		path{new Path()},
		aloader{new AnimationLoader()} {
	animation.push_back({skeleton});
	pose_seq = 0;
	path_offset = 0.0;
	makeState(skeleton->getNumBones(), &current_pose);
}

SkeletonTransform::SkeletonTransform(shared_ptr<Skeleton> skeleton, string file):
		speed_curve{},
		skeleton{skeleton},
		path{new Path()},
		aloader{new AnimationLoader()} {
	animation.push_back( *aloader->readAMC("assets/walk.amc", skeleton ) );
	animation.push_back( *aloader->readAMC("assets/kick.amc", skeleton ) );
	pose_seq = 0;
	path_offset = 0.0;
	makeState(skeleton->getNumBones(), &current_pose);
}

SkeletonTransform::~SkeletonTransform() {}

void SkeletonTransform::set_time(float time) {
	speed_curve.setTimeDisplay(time);

	/* work percentage of path travelled */
	path_offset = speed_curve.getDistanceValue(time) * path->getArcLength() / speed_curve.getTotalDistance();

	/* determine pose */
	// TODO: blend poses together
	animation[pose_seq].update( path_offset, &current_pose );
	skeleton->setCurrentPose( &current_pose );
}

void SkeletonTransform::apply_transform() {
	/* translate into position */
	path->translate( path_offset );
}

void SkeletonTransform::set_pose_seq(int ps) {
	pose_seq = ps;
}

void SkeletonTransform::reset() {
	animation.clear();
	animation.push_back({skeleton});
}

void SkeletonTransform::loadFile(string filename) {
	animation.clear();
	animation.push_back(*aloader->readAMC( filename.c_str(), skeleton ));
}

} /* namespace std */
