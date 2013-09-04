/*
 * AnimationLoader.cpp
 *
 *  Created on: 4/09/2013
 *      Author: remnanjona
 */

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "AnimationLoader.h"

namespace std {

AnimationLoader::AnimationLoader() {
	buffSize = 200;
	maxStates = 20000;
}

AnimationLoader::~AnimationLoader() {
	// TODO Auto-generated destructor stub
}

Animation *AnimationLoader::readAMC(FILE *file, int* , int &, Skeleton *skeleton) {
	printf("Reading animation\n");
	int numStates = 0;
	pose **state_list = new pose *[ maxStates ];
	pose *current;


	char *buff = new char[buffSize];
	char *p;
	while ((p = fgets(buff, buffSize, file)) != NULL) {
		char *start = buff;
		trim(&start);

		//Check if it is a comment or just empty
		if (start[0] == '#' || start[0] == ':' || start[0] == '\0') {
			continue;
		}

		if (start != NULL) {

			// create a new frame
			if ( isdigit( start[0] ) ) {
				current = makeState( skeleton->getNumBones() );
				state_list[ atoi(start)-1 ] = current;
				numStates++;
			}
			else {
				loadAMCStateBone( start, current, skeleton );
			}
		}
	}

	printf("Read %d frames\n", numStates);
	return new Animation(skeleton);
}

void AnimationLoader::loadAMCStateBone(char *buff, pose* current, Skeleton *skeleton) {
	char *start = buff;
	// read line as a set of angles, to apply to a particular part
	char n[32];
	float eularAngle[3];
	sscanf(start, "%s ", n);
	start += strlen(n);
	trim(&start);

	// match name in array


	bone *b = skeleton->getBone(n);
	if (b) {

		// read number of angles, depending on dof
		char next[32];
		if ((b->dof & DOF_ROOT) == DOF_ROOT) {

			for (int j = 0; sscanf(start, "%s", next) != 0 && j < 3; ++j) {
				((float *) &current->position)[j] = atof(next);
				start += strlen(next);
				trim(&start);
			}

			for (int j = 0; sscanf(start, "%s", next) != 0 && j < 3; ++j) {
				eularAngle[j] = atof(next);
				start += strlen(next);
				trim(&start);
			}

		} else {
			if ((b->dof & DOF_RX) == DOF_RX
					&& sscanf(start, "%s", next) != 0) {
				eularAngle[0] = atof(next);
				start += strlen(next);
				trim(&start);
			}
			if ((b->dof & DOF_RY) == DOF_RY
					&& sscanf(start, "%s", next) != 0) {
				eularAngle[1] = atof(next);
				start += strlen(next);
				trim(&start);
			}
			if ((b->dof & DOF_RZ) == DOF_RZ
					&& sscanf(start, "%s", next) != 0) {
				eularAngle[2] = atof(next);
				start += strlen(next);
				trim(&start);
			}
		}

		current->angle[b->index] = *fromEular(eularAngle[0], eularAngle[1], eularAngle[2]);
	}
	else {
		cout << n << " not found" << endl;
	}
}

} /* namespace std */
