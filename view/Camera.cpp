/*
 * Camera.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include "Camera.h"

namespace std {

Camera::Camera(SceneInterface *sc, float aspect) {
	click = NULL;
	scene = sc;
	cam_aspect = aspect;
	viewzoom = 100.0;
	cam_angle = new Quaternion(0, 0, 0, 1);
	focus = new Vec3D(0.0, 0.0, 0.0);
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}


void Camera::setCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0, cam_aspect, 1.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Camera::display() {
	setCamera();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -viewzoom);

	GLfloat *mat = new GLfloat [16];
	cam_angle->toMatrix(mat);
	glMultMatrixf(mat);

	float x = focus->getX(), y = focus->getY(), z = focus->getZ();
	gluLookAt(x, y, z, x, y, z + viewzoom, 0.0, -1.0, 0.0);

	scene->display();
	glPopMatrix();
}

void Camera::mouseClicked(int button, int state, int x, int y) {
	if (button == -1) {
		turn(x, y);
		click = getArc(x, y);
	}
	else if (!state) {
		click = getArc(x, y);
	}
}

void Camera::turn(int tx, int ty) {
	Quaternion drag = *getArc(tx, ty) * click->multiplicativeInverse();
	cam_angle = new Quaternion(drag * *cam_angle);

}

Quaternion *Camera::getArc(int ix, int iy) {
	float x = (ix - 400.0)/700.0;
	float y = (iy - 300.0)/700.0;
	float z = sqrt(1 - (x*x + y*y));
	return new Quaternion(0, x, y, z);
}


} /* namespace std */
