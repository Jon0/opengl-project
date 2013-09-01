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

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <GL/glut.h>

#include "Skeleton.h"

static float rad_to_deg = 360.0/(2 * M_PI);

Skeleton::Skeleton( int num, bone *bones ) {
	numBones = num;
	numStates = 0;
	root = bones;
	drawnState = NULL;
	select = NULL;
	idle = NULL;
	selIndex = -1;
	animate_frame = 0;
	show_animate = false;
	frame_rate = 1;

	// set pose
	defualtPose(true);
}

Skeleton::~Skeleton() {
	deleteBones(root);
}

void Skeleton::deleteBones(bone* root) {
	for (int i = 0; i < numBones; i++) {
		if (root[i].name != NULL) {
			free(root[i].name);
		}
		if (root[i].children != NULL) {
			free(root[i].children);
		}
	}
	free(root);
}

// [Assignment2] you may need to revise this function
void Skeleton::display() {
	if ( root == NULL || drawnState == NULL ) {
		return;
	}

	glPushMatrix();

	GLUquadric* quad = gluNewQuadric(); //Create a new quadric to allow you to draw cylinders
	if (quad == 0) {
		printf("Not enough memory to allocate space to draw\n");
		return;
	}
	//Actually draw the skeleton
	display(root, quad);

	gluDeleteQuadric(quad);
	glPopMatrix();

	if (show_animate && numStates > 0) {
		animate_frame = (numStates + animate_frame + frame_rate) % numStates;
		drawnState = state_list[animate_frame];
	}
}

// [Assignment2] you need to fill this function
void Skeleton::display(bone* root, GLUquadric* q) {
	if (root == NULL) {
		return;
	}

	//gluQuadricDrawStyle(q, r);
	state_rot *c_rot = drawnState->part[root->index];
	glPushMatrix();
	if ((root->dof & DOF_ROOT) == DOF_ROOT) {
		glTranslatef(drawnState->centre.x, drawnState->centre.y, drawnState->centre.z);
	}

	glRotatef(root->rotz, 0, 0, 1);
	glRotatef(root->roty, 0, 1, 0);
	glRotatef(root->rotx, 1, 0, 0);

	// rgb axis display
	glColor3f(1.0, 0.0, 0.0);
	display_cylinder(q, 1, 0, 0, 1, true);
	glColor3f(0.0, 1.0, 0.0);
	display_cylinder(q, 0, 1, 0, 1, true);
	glColor3f(0.0, 0.0, 1.0);
	display_cylinder(q, 0, 0, 1, 1, true);

	glRotatef(c_rot->degree[2], 0, 0, 1);
	glRotatef(c_rot->degree[1], 0, 1, 0);
	glRotatef(c_rot->degree[0], 1, 0, 0);

	glRotatef(root->rotx, -1, 0, 0);
	glRotatef(root->roty, 0, -1, 0);
	glRotatef(root->rotz, 0, 0, -1);

	if (root == select) {
		glColor3f(1.0, 1.0, 0.0);
		gluSphere(q, 0.50, 12, 12);
	}
	else {
		glColor3f(0.0, 1.0, 1.0);
		gluSphere(q, 0.25, 12, 12);
		glColor3f(1.0, 1.0, 1.0);
	}

	display_cylinder(q, root->dirx, root->diry, root->dirz, root->length, false);

	// draw children, translate into postition
	glPushMatrix();
	glTranslatef(root->dirx*root->length, root->diry*root->length, root->dirz*root->length);
	for (int i = 0; i < root->numChildren; ++i) {
		display(root->children[i], q);
	}
	glPopMatrix();
	glPopMatrix();
}

void Skeleton::displayId(bone* root, GLUquadric* q) {
	if (root == NULL) {
		return;
	}

	// id color
	glColor3ub(255, 0, root->index + 1);

	state_rot *c_rot = drawnState->part[root->index];
	glPushMatrix();
	if ((root->dof & DOF_ROOT) == DOF_ROOT) {
		glTranslatef(drawnState->centre.x, drawnState->centre.y, drawnState->centre.z);
	}

	glRotatef(root->rotz, 0, 0, 1);
	glRotatef(root->roty, 0, 1, 0);
	glRotatef(root->rotx, 1, 0, 0);

	// rgb axis display
	display_cylinder(q, 1, 0, 0, 1, true);
	display_cylinder(q, 0, 1, 0, 1, true);
	display_cylinder(q, 0, 0, 1, 1, true);

	glRotatef(c_rot->degree[2], 0, 0, 1);
	glRotatef(c_rot->degree[1], 0, 1, 0);
	glRotatef(c_rot->degree[0], 1, 0, 0);

	glRotatef(root->rotx, -1, 0, 0);
	glRotatef(root->roty, 0, -1, 0);
	glRotatef(root->rotz, 0, 0, -1);

	if (root == select) {
		gluSphere(q, 0.50, 12, 12);
	}
	else {
		gluSphere(q, 0.25, 12, 12);
	}

	display_cylinder(q, root->dirx, root->diry, root->dirz, root->length, false);

	// draw children, translate into postition
	glPushMatrix();
	glTranslatef(root->dirx*root->length, root->diry*root->length, root->dirz*root->length);
	for (int i = 0; i < root->numChildren; ++i) {
		displayId(root->children[i], q);
	}
	glPopMatrix();
	glPopMatrix();
}

void Skeleton::display_cylinder(GLUquadric* q, float x, float y, float z, float length, bool arrow) {
	Vec3D z_vec, d_vec;
	z_vec.x = 0;	z_vec.y = 0;	z_vec.z = 1;
	d_vec.x = x;	d_vec.y = y;	d_vec.z = z;
	Vec3D *a = &z_vec, *b = &d_vec;
	*a = a->crossProduct(*b);

	// dot product simplifies to z axis
	float angle = rad_to_deg * acos(z);
	float d = sqrt(a->x*a->x + a->y*a->y + a->z*a->z);

	// draw cylinder, rotated in correct direction
	glPushMatrix();

	if (d > 0) {
		glRotatef(angle, a->x, a->y, a->z);
	}
	gluCylinder(q, 0.08, 0.08, length, 10, 10);

	if (arrow) {
		glTranslatef(0.0, 0.0, length);
		glutSolidCone(0.16, 0.16, 8, 2);
	}

	glPopMatrix();
}

void Skeleton::defualtPose(bool reset) {
	// reset recreates initial pose
	if (reset) {
		//if (idle) delete idle;
		idle = makeState();
	}
	else if (!idle) {
		idle = makeState();
	}
	animate(false);
	drawnState = idle;
}

void Skeleton::animate(bool a) {
	select = NULL;
	show_animate = a;
}

void Skeleton::setPlaySpeed(int s) {
	frame_rate = s;
}

int Skeleton::selectMouse(int x, int y, GLfloat *proj, GLfloat *model) {
	if ( root == NULL || drawnState == NULL ) {
		return -1;
	}
	glEnable(GL_SCISSOR_TEST);
	glScissor(x, y, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(proj);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(model);

	glPushMatrix();
	GLUquadric* quad = gluNewQuadric(); //Create a new quadric to allow you to draw cylinders
	if (quad == 0) {
		printf("Not enough memory to allocate space to draw\n");
		return -1;
	}

	// draw the skeleton
	displayId(root, quad);

	gluDeleteQuadric(quad);
	glPopMatrix();

	GLubyte pix [4];
	glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pix);
	int selection = (int)pix[2] - 1;
	setSelection(selection);

	glDisable(GL_SCISSOR_TEST);
	return selection;
}

void Skeleton::setSelection(int i) {
	if (i < 0) {
		selIndex = -1;
		select = NULL;
		return;
	}
	show_animate = false;
	selIndex = i % numBones;
	select = &root[selIndex];
}

void Skeleton::modSelection(float x, float y, float z) {
	if ( drawnState == NULL || select == NULL ) {
		return;
	}
	if ((select->dof & DOF_RX) == DOF_RX) {
		drawnState->part[select->index]->degree[0] += x;
	}
	if ((select->dof & DOF_RY) == DOF_RY) {
		drawnState->part[select->index]->degree[1] += y;
	}
	if ((select->dof & DOF_RZ) == DOF_RZ) {
		drawnState->part[select->index]->degree[2] += z;
	}
}

bool Skeleton::hasSelection() {
	return select;
}

Vec3D *Skeleton::getCentre() {
	return &drawnState->centre;
}

state *Skeleton::makeState() {
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




