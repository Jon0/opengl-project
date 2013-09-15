/*
 * Camera.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <math.h>
#include "Camera.h"

namespace std {

Camera::Camera( SceneInterface *s, MainWindow *mw ):
		focus{0, 0, 0},
		cam_angle{1, 0, 0, 0},
		cam_angle_d{1, 0, 0, 0},
		click_old{1, 0, 0, 0},
		click_new{1, 0, 0, 0},
		button_state{} {
	scene = s;
	cam_aspect = 1.0;
	viewzoom = 100.0;

	// mouse action settings
	arcball_x = arcball_y = 0.0;
	arcball_radius = 1.0;

	wnd = mw;
	wnd->addView(this);
}

Camera::~Camera() {}

void Camera::setView( chrono::duration<double> tick ) {
	cam_angle.rotate( cam_angle_d );
	cam_angle_d = slerp( {1,0,0,0}, cam_angle_d, (1 - tick.count() * 10) );

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0, cam_aspect, 1.0, 1000.0);
	glGetFloatv(GL_PROJECTION_MATRIX, proj_matrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// setup camera position
	glPushMatrix();
	glTranslatef(0.0, 0.0, -viewzoom);
	cam_angle.toMatrix(temp_matrix);
	glMultMatrixf(temp_matrix);

	float x = focus.getX(), y = focus.getY(), z = focus.getZ();
	gluLookAt(x, y, z, x, y, z - viewzoom, 0.0, 1.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, model_matrix);

	scene->display( this, tick );
	glPopMatrix();
}

void Camera::resize(int x, int y) {
	cam_aspect = (double) x / (double) y;
	arcball_x = (x / 2.0);
	arcball_y = (y / 2.0);
	arcball_radius = (x / 2.0);
}

void Camera::keyPressed(unsigned char c) {
	scene->keyPressed(c);
}

int Camera::mouseClicked(int button, int state, int x, int y) {
	setupMatrix();
	button_state[button] = !state;
	if ( scene->mouseClicked( this, button, state, x, y ) ) return true;
	if (button_state[3]) {
		viewzoom /= 1.05;	// scroll back
		return true;
	}
	else if (button_state[4]) {
		viewzoom *= 1.05;	// scroll forward
		return true;
	}
	else if (!state) {
		getArc( arcball_x, arcball_y, x, y, arcball_radius, &click_new ); // initial click down
		click_old = click_new;
		return true;
	}

	//TODO: other controls

	return false;
}

int Camera::mouseDragged(int x, int y) {
	setupMatrix();
	if ( scene->mouseDragged( this, x, y ) ) return true;

	if (button_state[0]) {
		getArc(arcball_x, arcball_y, x, y, arcball_radius, &click_new);
		cam_angle_d = click_new * click_old.multiplicativeInverse();
		click_old = click_new;
		return true;
	}
	return false;
}

Quaternion Camera::cameraAngle() {
	return cam_angle;
}

void Camera::setupMatrix() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(proj_matrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(model_matrix);
}

GLfloat *Camera::getProjMatrix() {
	return proj_matrix;
}

GLfloat *Camera::getModelMatrix() {
	return model_matrix;
}

void getArc(int arcx, int arcy, int ix, int iy, float rad, Quaternion *result) {
	float x = (ix - arcx) / rad;
	float y = (iy - arcy) / rad;

	// check click is inside the arcball radius
	if (x*x + y*y < 1.0) {
		float z = sqrt(1 - (x*x + y*y));
		*result = Quaternion(0, x, y, z);
	}
	else {
		float len = sqrt(x*x + y*y);
		*result = Quaternion(0, x / len, y / len, 0);
	}
}


} /* namespace std */
