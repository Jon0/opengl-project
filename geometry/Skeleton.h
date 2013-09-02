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

#include <vector>
#include <GL/glut.h>

#include "../math/Vec3D.h"
#include "../math/Quaternion.h"

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
	Quaternion *angle; // use quaternion instead of degree
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

struct color {
	int *x, *y, *z, *bone, *sphere, *select;
};

class Skeleton;

typedef color *(Skeleton::*colorfunc)(bone *);

class Skeleton {
public:
	Skeleton( int num, bone *bones );
	~Skeleton();
	void addState();
	void display();
	void defualtPose(bool);
	void animate(bool);
	void setPlaySpeed(int s);
	int selectMouse(int, int, GLfloat *, GLfloat *);
	void setSelection(int);
	void modSelection(float, float, float);
	bool hasSelection();
	void setFrame(int);
	int getFrame();
	Vec3D *getCentre();
protected:
	state *makeState();
	state *copyState(state *);
private:
	int numBones, selIndex, colors[8];
	float animate_frame, frame_rate;

	// array of bones
	bone *root;
	bone *select;

	state *drawnState;	// current pose to draw
	state *drawnState_n;	// current pose to draw
	state *idle;	// Default pose
	vector<state *> animation;
	color *cStandard, *cAsId;

	bool show_animate;

	void deleteBones(bone *);
	void display(bone *, GLUquadric *, colorfunc cf);
	void displayId(bone *, GLUquadric *);
	void display_cylinder(GLUquadric *, float, float, float, float, bool);
	color *colorAsID(bone *);
	color *colorStandard(bone *);
};

#endif
