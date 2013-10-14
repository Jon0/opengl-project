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
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include <map>
#include <vector>

#include "Skeleton.h"

Skeleton::Skeleton( int numOfBones, bone *bones, map<string, vector<double> > *ws ) {
	numBones = numOfBones;
	root = bones;
	select = NULL;
	selQuat = glm::quat();
	selIndex = -1;
	current_pose = NULL;

	colors[0] = 0;			// id
	colors[1] = 0xff0000ff;	// red
	colors[2] = 0xff00ff00;	// green
	colors[3] = 0xffff0000;	// blue
	colors[4] = 0xffffffff;	// white
	colors[5] = 0xffffff00;	// teal
	colors[6] = 0xff00ffff;	// yellow

	cAsId = new color();
	cStandard = new color();
	int **a = (int **)cStandard;
	int **b = (int **)cAsId;
	for (int i = 0; i < 6; ++i) {
		a[i] = &colors[i+1];
		b[i] = &colors[0];
	}

	// default colour function
	cf = &Skeleton::colorStandard;

	weights = ws;
}

Skeleton::~Skeleton() {
	deleteBones(root);
	delete weights;
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

int Skeleton::getNumBones() {
	return numBones;
}

bone *Skeleton::getBone(char *name) {
	for (int i = 0; i < numBones; ++i) {
		if (strcmp(name, root[i].name) == 0) {
			return &root[i];
		}
	}
	return NULL;
}

bone *Skeleton::getBone(int ind) {
	return &root[ind];
}

// [Assignment2] you may need to revise this function
void Skeleton::display() {
	if ( root == NULL || current_pose == NULL ) {
		return;
	}

	GLUquadric* quad = gluNewQuadric(); //Create a new quadric to allow you to draw cylinders
	if (quad == 0) {
		printf("Not enough memory to allocate space to draw\n");
		return;
	}
	//gluQuadricDrawStyle(q, r);

	//Actually draw the skeleton
	glPushMatrix();
	glTranslatef(current_pose->adjust.x, current_pose->adjust.y, current_pose->adjust.z);
	display(root, quad);
	glPopMatrix();

	gluDeleteQuadric(quad);
}

// [Assignment2] you need to fill this function
void Skeleton::display(bone* root, GLUquadric* q) {
	if (root == NULL) {
		return;
	}
	color *cl = (this->*cf)(root);

	glPushMatrix();
	glMultMatrixf(&glm::mat4_cast( root->rotation )[0][0]);

	// rgb axis display
	glColor4ubv((unsigned char *) cl->x);
	display_cylinder(q, 1, 0, 0, 1, true);
	glColor4ubv((unsigned char *) cl->y);
	display_cylinder(q, 0, 1, 0, 1, true);
	glColor4ubv((unsigned char *) cl->z);
	display_cylinder(q, 0, 0, 1, 1, true);


	glMultMatrixf(&glm::mat4_cast( current_pose->q.data()[root->index] )[0][0]);
	glMultMatrixf(&glm::mat4_cast( glm::inverse(root->rotation) )[0][0]);

	if (root == select) {
		glColor4ubv((unsigned char *) cl->select);
		gluSphere(q, 0.50, 12, 12);
	    GLint viewport[4];
	    GLdouble modelview[16];
	    GLdouble projection[16];
	    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	    glGetDoublev( GL_PROJECTION_MATRIX, projection );
	    glGetIntegerv( GL_VIEWPORT, viewport );
		gluProject(0, 0, 0, modelview, projection, viewport, &selPoint[0], &selPoint[1], &selPoint[2]);

		// sum the rotations back to the root
		selQuat = glm::quat();
		bone *b = root->parent;
		while(b) {
			glm::quat q = current_pose->q.data()[b->index];
			glm::quat bri = glm::inverse(b->rotation);
			selQuat = bri * selQuat;
			selQuat = q * selQuat;
			selQuat = b->rotation * selQuat;
			b = b->parent;
		}
	}
	else {
		glColor4ubv((unsigned char *) cl->sphere);
		gluSphere(q, 0.25, 12, 12);
		glColor4ubv((unsigned char *) cl->bone);
	}
	display_cylinder(q, root->dirx, root->diry, root->dirz, root->length, false);

	// draw children, translate into position
	glPushMatrix();
	glTranslatef(root->dirx*root->length, root->diry*root->length, root->dirz*root->length);
	for (int i = 0; i < root->numChildren; ++i) {
		display( root->children[i], q );
	}
	glPopMatrix();
	glPopMatrix();
}

void Skeleton::display_cylinder(GLUquadric* q, float x, float y, float z, float length, bool arrow) {
	Vec3D z_vec, d_vec;
	z_vec.v[0] = 0;	z_vec.v[1] = 0;	z_vec.v[2] = 1;
	d_vec.v[0] = x;	d_vec.v[1] = y;	d_vec.v[2] = z;
	Vec3D *a = &z_vec, *b = &d_vec;
	*a = a->crossProduct(*b);

	// dot product simplifies to z axis
	float angle = rad_to_deg * acos(z);
	float d = sqrt(a->v[0]*a->v[0] + a->v[1]*a->v[1] + a->v[2]*a->v[2]);

	// draw cylinder, rotated in correct direction
	glPushMatrix();

	if (d > 0) {
		glRotatef(angle, a->v[0], a->v[1], a->v[2]);
	}
	gluCylinder(q, 0.08, 0.08, length, 10, 10);

	if (arrow) {
		glTranslatef(0.0, 0.0, length);
		glutSolidCone(0.16, 0.16, 8, 2);
	}

	glPopMatrix();
}


int Skeleton::selectMouse(int x, int y) {
	glEnable(GL_SCISSOR_TEST);
	glScissor(x, y, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	cf = &Skeleton::colorAsID;
	display();
	cf = &Skeleton::colorStandard;

	glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pix);
	glDisable(GL_SCISSOR_TEST);
	return (int)pix[0] - 1;
}

void Skeleton::setSelection(int i) {
	if (i < 0) {
		selIndex = -1;
		select = NULL;
		return;
	}
	selIndex = i % numBones;
	select = &root[selIndex];
}

bool Skeleton::hasSelection() {
	return select;
}

DOF Skeleton::getDof(int i) {
	return root[i].dof;
}

GLdouble *Skeleton::selectionCenter() {
	return selPoint;
}

glm::quat Skeleton::getSelectionRot() {
	return selQuat;
}

glm::quat Skeleton::getBoneAxis(int id) {
	return root[id].rotation;
}

void Skeleton::setCurrentPose(pose *p) {
	current_pose = p;
}

color *Skeleton::colorAsID(bone *b) {
	colors[0] = b->index + 1;
	return cAsId;
}

color *Skeleton::colorStandard(bone *b) {
	return cStandard;
}

void makeState( int numBones, pose *next ) {
	next->adjust = glm::vec3(0, 0, 0);
	next->q.reserve(numBones);

	for (int i = 0; i < numBones; ++i) {
		next->q.push_back( glm::quat() );
	}
}

// TODO: does this work?
void copyState( int numBones, pose *other, pose *next ) {
	next->adjust = other->adjust;
	next->q.reserve(numBones);

	for (int i = 0; i < numBones; ++i) {
		next->q.push_back( other->q.data()[i] );
	}
}


