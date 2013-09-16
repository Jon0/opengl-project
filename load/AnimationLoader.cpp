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
#include "../spline/DynamicPose.h"
#include "AnimationLoader.h"

namespace std {

AnimationLoader::AnimationLoader() {
	buffSize = 200;
	maxStates = 20000;
}

AnimationLoader::~AnimationLoader() {}

DynamicPose *AnimationLoader::readAMC( const char *filename, shared_ptr<Skeleton> skeleton ) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Failed to open file %s\n", filename);
		return NULL;
	}
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
				current = new pose();
				makeState( skeleton->getNumBones(), current );
				state_list[ atoi(start)-1 ] = current;
				numStates++;
			}
			else {
				loadAMCStateBone( start, current, skeleton );
			}
		}
	}

	// adjust pose movements
	Vec3D start = state_list[0]->adjust, end = state_list[numStates - 1]->adjust;
	for (int i = 0; i < numStates; ++i) {
		float percent = (float) i / (float) numStates;
		Vec3D current = start * (1 - percent) + end * percent;
		state_list[i]->adjust = state_list[i]->adjust - current;
	}

	delete[] buff;
	fclose(file);
	printf("Read %d frames\n", numStates);
	DynamicPose *a = new DynamicPose(numStates, state_list, skeleton);
	a->setPathLength( start.getDistance(end) );

	// TODO: make speed curve
	delete state_list; // hopefully it gets copied by animation
	return a;
}

void AnimationLoader::loadAMCStateBone( char *buff, pose *current, shared_ptr<Skeleton> skeleton ) {
	char *start = buff;
	// read line as a set of angles, to apply to a particular part
	char n[32];
	float eularAngle[3]{0, 0, 0};
	sscanf(start, "%s ", n);
	start += strlen(n);
	trim(&start);

	// match name in array


	bone *b = skeleton->getBone(n);
	if (b) {

		// read number of angles, depending on dof
		char next[32];
		if ((b->dof & DOF_ROOT) == DOF_ROOT) {

			float v[3];
			for (int j = 0; sscanf(start, "%s", next) != 0 && j < 3; ++j) {
				v[j] = atof(next);
				start += strlen(next);
				trim(&start);
			}
			current->adjust = Vec3D(v);

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

		current->q.data()[b->index] = *fromEular(eularAngle[0], eularAngle[1], eularAngle[2]);
	}
	else {
		cout << n << " not found" << endl;
	}
}

} /* namespace std */
