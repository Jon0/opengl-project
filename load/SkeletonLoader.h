/*
 * SkeletonLoader.h
 *
 *  Created on: 1/09/2013
 *      Author: remnanjona
 */

#ifndef SKELETONLOADER_H_
#define SKELETONLOADER_H_

#include <stdio.h>
#include <GL/glut.h>
#include "../geometry/Skeleton.h"

namespace std {

void trim(char**);

class SkeletonLoader {
public:
	SkeletonLoader();
	virtual ~SkeletonLoader();
	Skeleton *readASF( const char * );
	void readAMC(FILE*, int* , int &, bone *);
	void saveAMCState( char *, int , bone *, state * );
	void loadAMCState( char *, int , bone *, state * );

protected:
	void readHeading(char *, FILE *, int &, bone *);
	void readHierarchy(char*, FILE *, int &, bone * );
	void readBone(char *, FILE *, int &, bone * );
	DOF dofFromString(char* s);
	void decomment(char *);
	state *makeState(int);
	void loadAMCStateBone( char *, state *, int &, bone * );

private:
	int buffSize, maxBones, maxStates;
};

} /* namespace std */
#endif /* SKELETONLOADER_H_ */
