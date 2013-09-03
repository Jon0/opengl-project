/*
 * SkeletonLoader.h
 *
 *  Created on: 1/09/2013
 *      Author: remnanjona
 */

#ifndef SKELETONLOADER_H_
#define SKELETONLOADER_H_

#include <stdio.h>
#include "../geometry/Skeleton.h"

namespace std {

void trim(char**);

class SkeletonLoader {
public:
	SkeletonLoader();
	virtual ~SkeletonLoader();
	Skeleton *readASF( const char * );

protected:
	void readHeading(char *, FILE *, int &, bone *);
	void readHierarchy(char*, FILE *, int &, bone * );
	void readBone(char *, FILE *, int &, bone * );
	DOF dofFromString(char* s);
	void decomment(char *);

private:
	int buffSize, maxBones;
};

} /* namespace std */
#endif /* SKELETONLOADER_H_ */
