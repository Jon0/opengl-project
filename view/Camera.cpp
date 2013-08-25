/*
 * Camera.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <GL/glut.h>
#include "Camera.h"

namespace std {

Camera::Camera(SceneInterface *sc) {
	focus = new Vec3D(0.0, 0.0, 0.0);
	scene = sc;
	viewzoom = 100.0;
	angletilt = angleflat = 0.0;
	setCamera();
}

void Camera::setCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0, (double) 800 / (double) 600, 1.0, 1000.0);
}


void Camera::display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 7.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	glTranslatef(0.0, 0.0, -viewzoom);
	glRotatef(angletilt, 1.0, 0.0, 0.0);
	glRotatef(angleflat, 0.0, 1.0, 0.0);

	float x = focus->getX(), y = focus->getY(), z = focus->getZ();
	gluLookAt(x, y, z, x, y, z + viewzoom, 0.0, 1.0, 0.0);

	scene->display();
	glPopMatrix();
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
