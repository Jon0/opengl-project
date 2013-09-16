/*
 * AnimationLoader.h
 *
 *  Created on: 4/09/2013
 *      Author: remnanjona
 */

#ifndef ANIMATIONLOADER_H_
#define ANIMATIONLOADER_H_

#include <memory>
#include "SkeletonLoader.h"
#include "../spline/Path.h"
#include "../spline/DynamicPose.h"

namespace std {

class AnimationLoader {
public:
	AnimationLoader();
	virtual ~AnimationLoader();
	DynamicPose *readAMC( const char *, shared_ptr<Skeleton> );
	pose loadAMCState( const char *, shared_ptr<Skeleton> );
	void saveAMCState( const char *, pose *drawnState, shared_ptr<Skeleton> );

private:
	int buffSize, maxStates;
	void loadAMCStateBone( char *buff, pose *current, shared_ptr<Skeleton> );
	void loadAMCQBone( char *, pose *, shared_ptr<Skeleton> );
};

} /* namespace std */
#endif /* ANIMATIONLOADER_H_ */
