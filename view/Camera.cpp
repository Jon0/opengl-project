/*
 * Camera.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <GL/glut.h>
#include "Camera.h"

namespace std {

Camera::Camera(SceneInterface *sc, float aspect) {
	focus = new Vec3D(0.0, 0.0, 0.0);
	scene = sc;
	cam_aspect = aspect;
	viewzoom = 100.0;
	angletilt = angleflat = 0.0;
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
