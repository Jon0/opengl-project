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

struct pose {
	Vec3D position;
	Quaternion *angle;
};

//Type to represent a bone
struct bone {
	int index;
	char* name;
	float dirx, diry, dirz;
	float rotx, roty, rotz;
	Quaternion *rotation;
	DOF dof;
	float length;
	bone *parent;
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
	Skeleton( int, bone * );
	~Skeleton();

	void display(pose *p);
	int getNumBones();
	bone *getBone(char *);
	int selectMouse(int, int, pose *p);
	void setSelection(int);
	bool hasSelection();
	DOF getDof(int);
	GLdouble *selectionCenter();
	Quaternion *getSelectionRot();
	Quaternion *getBoneRot(int);

protected:
	void deleteBones(bone *);
	void display(bone *, GLUquadric *, pose *p);
	void display_cylinder(GLUquadric *, float, float, float, float, bool);

private:
	int numBones, selIndex, colors[8];
	colorfunc cf;
	GLubyte pix[4]; // buffer to return selection
	GLfloat temp_mat[16];
	GLdouble selPoint[3];
	Quaternion *selQuat;

	// array of bones
	bone *root;
	bone *select;
	color *cStandard, *cAsId;

	// color functions
	color *colorAsID(bone *);
	color *colorStandard(bone *);
};

#endif
