/*
 * SkeletonLoader.cpp
 *
 *  Created on: 1/09/2013
 *      Author: remnanjona
 */

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "SkeletonLoader.h"

namespace std {

SkeletonLoader::SkeletonLoader() {
	buffSize = 200;
	maxBones = 60;
	maxStates = 20000;
}

SkeletonLoader::~SkeletonLoader() {
	// TODO Auto-generated destructor stub
}

Skeleton *SkeletonLoader::readASF(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Failed to open file %s\n", filename);
		return NULL;
	}

	bone *root = new bone [maxBones];
	for (int i = 0; i < maxBones; i++) {
		root[i].index = i;
		root[i].dirx = 0;
		root[i].diry = 0;
		root[i].dirz = 0;
		root[i].rotx = 0;
		root[i].roty = 0;
		root[i].rotz = 0;
		root[i].dof = DOF_NONE;
		root[i].length = 0;
		root[i].name = NULL;
		root[i].numChildren = 0;
		root[i].children = (bone**) malloc(sizeof(bone*) * 5);
	}

	char *name = new char[5];
	name[0] = 'r';
	name[1] = name[2] = 'o';
	name[3] = 't';
	name[4] = '\0';
	root[0].name = name;
	root[0].dof = DOF_ROOT;
	root[0].index = 0;


	int numBones = 1;
	char* buff = new char[buffSize];
	char *p;

	printf("Starting reading skeleton file\n");
	while ((p = fgets(buff, buffSize, file)) != NULL) {
		//Reading actually happened!
		char* start = buff;
		trim(&start);

		//Check if it is a comment or just empty
		if (buff[0] == '#' || buff[0] == '\0') {
			continue;
		}

		start = strchr(buff, ':');
		if (start != NULL) {
			//This actually is a heading
			//Reading may actually consume the next heading
			//so headings need to be a recursive construct?
			readHeading(buff, file, numBones, root);
		}
	}

	delete[] buff;
	fclose(file);

	// make a copy with actual array length, also remap children
	bone *bones = new bone [numBones];
	for (int i = 0; i < numBones; ++i) {
		memcpy(&bones[i], &root[i], sizeof(bone));
		bones[i].children = (bone**) malloc(sizeof(bone*) * 5);
		for (int j = 0; j < root[i].numChildren; ++j) {
			bones[i].children[j] = &bones[root[i].children[j]->index];
		}
		delete root[i].children;
	}
	delete root;

	Skeleton *skel = new Skeleton(numBones, bones);
	printf("Completed reading skeleton file\n");
	return skel;
}


/**
 * Trim the current string, by adding a null character into where the comments start
 */
void SkeletonLoader::decomment(char * buff) {
	char* comStart = strchr(buff, '#');
	if (comStart != NULL) {
		//remove irrelevant part of string
		*comStart = '\0';
	}
}

void SkeletonLoader::readHeading( char* buff, FILE* file, int &numBones, bone *root ) {
	char* temp = buff;
	decomment(buff);
	trim(&temp);

	char head[50];
	char rest[200];
	int num = sscanf(temp, ":%s %s", head, rest);
	if (num == 0) {
		printf("Could not get heading name from %s, all is lost\n", temp);
		exit(EXIT_FAILURE);
	}
	if (strcmp(head, "version") == 0) {
		//version string - must be 1.10
		char* version = rest;
		if (num != 2) {
			char *p = { '\0' };
			while (strlen(p) == 0) {
				char* p = fgets(buff, buffSize, file);
				decomment(p);
				trim(&p);
				version = p;
			}
		}
		if (strcmp(version, "1.10") != 0) {
			printf("Invalid version: %s, must be 1.10\n", version);
			exit(EXIT_FAILURE);
		}
		//Finished reading version so read the next thing?
	} else if (strcmp(head, "name") == 0) {
		//This allows the skeleton to be called something
		//other than the file name
		//We don't actually care what the name is, so can
		//ignore this whole section

	} else if (strcmp(head, "documentation") == 0) {
		//Documentation section has no meaningful information
		//only of use if you want to copy the file. So we skip it
	} else if (strcmp(head, "units") == 0) {
		//Has factors for the units
		//To be able to model the real person,
		//these must be parsed correctly
		//Only really need to check if deg or rad, but even
		//that is probably not needed for the core or extension
	} else if (strcmp(head, "root") == 0) {
		//Read in information about root
		//Or be lazy and just assume it is going to be the normal CMU thing!
	} else if (strcmp(head, "bonedata") == 0) {
		//Description of each bone
		//This does need to actually be read :(
		char *p;
		while ((p = fgets(buff, buffSize, file)) != NULL) {
			decomment(p);
			trim(&p);
			if (strlen(p) > 0) {
				if (p[0] == ':') {

					return readHeading(buff, file, numBones, root);
				} else if (strcmp(p, "begin") != 0) {
					printf("Expected begin for bone data %d, found \"%s\"", numBones, p);
					exit(EXIT_FAILURE);
				} else {
					readBone(buff, file, numBones, root);
					numBones++;
				}

			}
		}
	} else if (strcmp(head, "hierarchy") == 0) {
		//Description of how the bones fit together
		char *p;
		while ((p = fgets(buff, buffSize, file)) != NULL) {
			trim(&p);
			decomment(p);
			if (strlen(p) > 0) {
				if (p[0] == ':') {
					return readHeading(buff, file, numBones, root);
				} else if (strcmp(p, "begin") != 0) {
					printf("Expected begin in hierarchy, found %s", p);
					exit(EXIT_FAILURE);
				} else {
					readHierarchy(buff, file, numBones, root);
				}

			}
		}
	} else {
		printf("Unknown heading %s\n", head);
	}

}

void SkeletonLoader::readHierarchy(char* buff, FILE* file, int &numBones, bone *root ) {
	char *p;
	char t1[200];
	while ((p = fgets(buff, buffSize, file)) != NULL) {
		trim(&p);
		decomment(p);
		if (strlen(p) > 0) {
			if (strcmp(p, "end") == 0) {
				//end of hierarchy
				return;
			} else {
				//Read the root node
				sscanf(p, "%s ", t1);
				bone* rootBone = NULL;
				for (int i = 0; i < numBones; i++) {
					if (strcmp(root[i].name, t1) == 0) {
						rootBone = root + i;
						break;
					}
				}
				//Read the connections
				p += strlen(t1);
				bone* other = NULL;
				while (*p != '\0') {
					sscanf(p, "%s ", t1);

					for (int i = 0; i < numBones; i++) {
						if (strcmp(root[i].name, t1) == 0) {
							other = root + i;
							break;
						}
					}
					if (other == NULL) {
						printf("Unknown bone %s found in hierarchy. Failure", t1);
						exit(EXIT_FAILURE);
					}
					rootBone->children[rootBone->numChildren] = other;
					rootBone->numChildren++;
					p += strlen(t1) + 1;

				}
			}
		}

	}
}

void SkeletonLoader::readBone(char* buff, FILE* file, int &numBones, bone *root ) {
	char *p;
	char t1[50];
	while ((p = fgets(buff, buffSize, file)) != NULL) {
		trim(&p);
		decomment(p);
		if (strlen(p) > 0) {
			if (strcmp(p, "end") == 0) {
				//end of this bone
				return;
			} else {
				sscanf(p, "%s ", t1);
				if (strcmp(t1, "name") == 0) {

					//Read the name and actually remember it
					char* name = (char*) malloc(sizeof(char) * 10);
					sscanf(p, "name %s", name);
					root[numBones].name = name;
					//root[numBones].index = numBones;
					//names[numBones] = &root[numBones];
				} else if (strcmp(t1, "direction") == 0) {
					//Also actually important
					float x, y, z;
					sscanf(p, "direction %f %f %f", &x, &y, &z);
					root[numBones].dirx = x;
					root[numBones].diry = y;
					root[numBones].dirz = z;
				} else if (strcmp(t1, "length") == 0) {
					//Also actually important
					float len;
					sscanf(p, "length %f", &len);
					root[numBones].length = len;
				} else if (strcmp(t1, "dof") == 0) {
					//Read the degrees of freedom!
					char d1[5];
					char d2[5];
					char d3[5];
					int num = sscanf(p, "dof %s %s %s", d1, d2, d3);
					switch (num) {
					DOF dof;
				case 3:
					dof = dofFromString(d3);
					root[numBones].dof = root[numBones].dof | dof;
					//fallthrough!!
					/* no break */
				case 2:
					dof = dofFromString(d2);
					root[numBones].dof = root[numBones].dof | dof;
					//fallthrough!!
					/* no break */
				case 1:
					dof = dofFromString(d1);
					root[numBones].dof = root[numBones].dof | dof;
					break;
					}
				} else if (strcmp(t1, "axis") == 0) {
					//Read the rotation axis
					float x, y, z;
					int num = sscanf(p, "axis %f %f %f XYZ", &x, &y, &z);
					if (num != 3) {
						printf("axis format doesn't match expected\n");
						printf("Expected: axis %%f %%f %%f XYZ\n");
						printf("Got: %s", p);
						exit(EXIT_FAILURE);
					}
					root[numBones].rotx = x;
					root[numBones].roty = y;
					root[numBones].rotz = z;
				}
				//There are more things but they are not needed for the core
			}

		}
	}
}

/**
 * Helper function to turn a DOF from the AMC file into the correct DOF value
 */
DOF SkeletonLoader::dofFromString(char* s) {
	if (strcmp(s, "rx") == 0)
		return DOF_RX;
	if (strcmp(s, "ry") == 0)
		return DOF_RY;
	if (strcmp(s, "rz") == 0)
		return DOF_RZ;
	printf("Unknown DOF found: %s", s);
	return DOF_NONE;
}

/*
 * Remove leading and trailing whitespace. Increments the
 * pointer until it points to a non whitespace char
 * and then adds nulls to the end until it has no
 * whitespace on the end
 */
void trim(char **p) {
	if (p == NULL) {
		printf("File terminated without version number!\n");
		exit(EXIT_FAILURE);
	}

	//Remove leading whitespace
	while (**p == ' ' || **p == '\t') {
		(*p)++;
	}

	int len = strlen(*p);
	while (len > 0) {
		char last = (*p)[len - 1];
		if (last == '\r' || last == '\n' || last == ' ' || last == '\t') {
			(*p)[--len] = '\0';
		} else {
			return;
		}
	}
}

void SkeletonLoader::readAMC(FILE* file, int* i, int &numBones, bone *root) {
	printf("Reading animation\n");
	int numStates = 0;
	state **state_list = new state *[ maxStates ];
	state *current;


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
				current = makeState(numBones);
				state_list[ atoi(start)-1 ] = current;
				numStates++;
			}
			else {
				loadAMCStateBone(start, current, numBones, root);
			}
		}
	}

	printf("Read %d frames\n", numStates);
}

void SkeletonLoader::loadAMCStateBone( char *buff, state* current, int &numBones, bone *root ) {
	char *start = buff;
	// read line as a set of angles, to apply to a particular part
					bool found = false;
					char n[32];
					sscanf(start, "%s ", n);
					start += strlen(n);
					trim(&start);

					// match name in array
					for (int i = 0; i < numBones; ++i) {
						if (strcmp(n, root[i].name) == 0) {

							// read number of angles, depending on dof
							char next[32];

							if ((root[i].dof & DOF_ROOT) == DOF_ROOT) {


								for (int j = 0; sscanf(start, "%s", next) != 0 && j < 3; ++j) {
									((float *) &current->centre)[j] = atof(next);
									start += strlen(next);
									trim(&start);
								}

								for (int j = 0; sscanf(start, "%s", next) != 0 && j < 3; ++j) {
									current->part[i]->degree[j] = atof(next);
									start += strlen(next);
									trim(&start);
								}


							} else {
								if ((root[i].dof & DOF_RX) == DOF_RX && sscanf(start, "%s", next) != 0) {
									current->part[i]->degree[0] = atof(next);
									start += strlen(next);
									trim(&start);
								}
								if ((root[i].dof & DOF_RY) == DOF_RY && sscanf(start, "%s", next) != 0) {
									current->part[i]->degree[1] = atof(next);
									start += strlen(next);
									trim(&start);
								}
								if ((root[i].dof & DOF_RZ) == DOF_RZ && sscanf(start, "%s", next) != 0) {
									current->part[i]->degree[2] = atof(next);
									start += strlen(next);
									trim(&start);
								}
							}

							found = true;
							break;
						}
					}
					if (!found) cout << n << " not found" << endl;
}


state *SkeletonLoader::makeState(int numBones) {
	state *current = new state();
	current->part = new state_rot *[numBones];

	for (int i = 0; i < numBones; ++i) {
		current->part[i] = new state_rot();
		current->part[i]->degree = new float [ 3 ];
		current->part[i]->degree[0] = 0;
		current->part[i]->degree[1] = 0;
		current->part[i]->degree[2] = 0;
		current->part[i]->size = 3;
	}
	return current;
}

void SkeletonLoader::saveAMCState( char *filename, int numBones, bone *root, state *drawnState ) {
	cout << "save to file: " << filename << endl;
	FILE* f = fopen(filename, "w");

	for (int i = 0; i < numBones; ++i) {
		if (root[i].dof != 0) {
			fprintf(f, "%s ", root[i].name);
			float *ang = drawnState->part[root[i].index]->degree;
			if ((root[i].dof & DOF_ROOT) == DOF_ROOT) {
				fprintf(f, "%f ", drawnState->centre.x);
				fprintf(f, "%f ", drawnState->centre.y);
				fprintf(f, "%f", drawnState->centre.z);
				fprintf(f, "%f ", ang[0]);
				fprintf(f, "%f ", ang[1]);
				fprintf(f, "%f ", ang[2]);
			}
			else {
				if ((root[i].dof & DOF_RX) == DOF_RX) fprintf(f, "%f ", ang[0]);
				if ((root[i].dof & DOF_RY) == DOF_RY) fprintf(f, "%f ", ang[1]);
				if ((root[i].dof & DOF_RZ) == DOF_RZ) fprintf(f, "%f ", ang[2]);
			}



			fprintf(f, "\n");
		}
	}
	fclose(f);
}

void SkeletonLoader::loadAMCState( char *filename, int numBones, bone *root, state *drawnState ) {
	FILE* file = fopen(filename, "r");
	if (!file) {
		cout << "file not found" << endl;
		return;
	}
	printf( "Reading pose: %s\n", filename );
	state *current = makeState(numBones);	// get blank state

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
			// read frame
			if ( !isdigit( start[0] ) ) {
				loadAMCStateBone(start, current, numBones, root);
			}
		}
	}
}

} /* namespace std */
