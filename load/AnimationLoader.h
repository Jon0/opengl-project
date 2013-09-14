/*
 * AnimationLoader.h
 *
 *  Created on: 4/09/2013
 *      Author: remnanjona
 */

#ifndef ANIMATIONLOADER_H_
#define ANIMATIONLOADER_H_

#include <stdio.h>
#include "SkeletonLoader.h"
#include "../spline/Path.h"
#include "../spline/Animation.h"

namespace std {

class AnimationLoader {
public:
	AnimationLoader();
	virtual ~AnimationLoader();
	Animation *readAMC( const char *, Skeleton *, Path *path);

private:
	int buffSize, maxStates;
	void loadAMCStateBone( char *buff, pose *current, Skeleton *, Path *path );
};

} /* namespace std */
#endif /* ANIMATIONLOADER_H_ */
