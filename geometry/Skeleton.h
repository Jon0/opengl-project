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
#include <glm/gtc/quaternion.hpp>

#include "Drawable.h"
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
	glm::vec3 adjust;
	vector<glm::quat> q;
};

//Type to represent a bone
struct bone {
	int index;
	char* name;
	float dirx, diry, dirz;
	glm::quat rotation;
	DOF dof;
	float length;
	bone *parent;
	bone** children;
	int numChildren;
};

struct color {
	int *x, *y, *z, *bone, *sphere, *select;
};

void makeState(int, pose *);
void copyState(int, pose *, pose *);

class Skeleton;

typedef color *(Skeleton::*colorfunc)(bone *);

class Skeleton: public Drawable {
public:
	Skeleton( int, bone * );
	~Skeleton();

	virtual void display();
	virtual int selectMouse(int, int);

	int getNumBones();
	bone *getBone(char *);
	bone *getBone(int);

	void setSelection(int);
	bool hasSelection();
	DOF getDof(int);
	GLdouble *selectionCenter();
	glm::quat getSelectionRot();
	glm::quat getBoneAxis(int);
	void setCurrentPose(pose *p);


protected:
	void deleteBones(bone *);
	void display(bone *, GLUquadric *);
	void display_cylinder(GLUquadric *, float, float, float, float, bool);

private:
	int numBones, selIndex, colors[8];
	colorfunc cf;
	GLubyte pix[4]; // buffer to return selection
	GLfloat temp_mat[16];
	GLdouble selPoint[3];
	glm::quat selQuat;

	// current pose
	pose *current_pose;

	// array of bones
	bone *root;
	bone *select;
	color *cStandard, *cAsId;

	// color functions
	color *colorAsID(bone *);
	color *colorStandard(bone *);
};

#endif
