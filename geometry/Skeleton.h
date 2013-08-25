//---------------------------------------------------------------------------
//
// This software is provided 'as-is' for assignment of COMP308
// in ECS, Victoria University of Wellington,
// without any express or implied warranty.
// In no event will the authors be held liable for any
// damages arising from the use of this software.
//
// The contents of this file may not be copied or duplicated in any form
// without the prior permission of its owner.
//
// Copyright (c) 2012 by Taehyun Rhee
//
// Edited by Roma Klapaukh, Daniel Atkins, and Taehyun Rhee
//
//---------------------------------------------------------------------------

#ifndef SKELETONH
#define SKELETONH

#include <stdio.h>
#include <GL/glut.h>

#include "../math/Vec3D.h"

using namespace std;

// Using bitmasking to denote different degrees of freedom for joint motion
typedef int DOF;

#define DOF_NONE 0
#define DOF_RX 1
#define DOF_RY 2
#define DOF_RZ 4
#define DOF_ROOT 8 // Root has 6, 3 translation and 3 rotation

struct state_rot {
	int size;
	char *name;
	float *degree;
};

struct state {
	Vec3D centre;
	state_rot **part;
};

//Type to represent a bone
struct bone {
	int index;
	char* name;
	float dirx, diry, dirz;
	float rotx, roty, rotz;
	DOF dof;
	float length;
	bone** children;
	int numChildren;
};

void trim(char**);

class Skeleton {

private:
	int buffSize, maxBones, numStates, maxStates, animate_frame, selIndex, frame_rate;

	// array of bones
	bone *root;
	bone *select;

	state *drawnState;	// current pose to draw
	state *idle;	// Default pose
	state **state_list;	// buffer of animated poses

	bool show_animate;
	bool readASF(char*);
	void readHeading(char*, FILE*);
	void decomment(char*);
	void deleteBones(bone*);
	void readBone(char*, FILE*);
	void readHierarchy(char*, FILE*);
	void display(bone*, GLUquadric*);
	void display_cylinder(GLUquadric*, float, float, float, float, bool);
	DOF dofFromString(char*);
	state *makeState();
	void loadAMCStateBone( char *buff, state* current );

public:
	int numBones;
	Skeleton(char*, char*);
	~Skeleton();
	void display();
	void defualtPose(bool);
	void animate(bool);
	void setPlaySpeed(int s);
	void incSelection();
	void modSelection(float, float, float);
	Vec3D *getCentre();
	void readAMC(FILE*,int*);
	void saveAMCState( char *filename );
	void loadAMCState( char *filename );
};

#endif
