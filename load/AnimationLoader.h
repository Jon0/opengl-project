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
#include "../animation/Animation.h"

namespace std {

class AnimationLoader {
public:
	AnimationLoader();
	virtual ~AnimationLoader();
	Animation *readAMC( const char *, Skeleton *);

private:
	int buffSize, maxStates;
	void loadAMCStateBone( char *buff, pose* current, Skeleton * );
};

} /* namespace std */
#endif /* ANIMATIONLOADER_H_ */
