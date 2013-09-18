/*
 * Camera.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <math.h>
#include "Camera.h"

namespace std {

Camera::Camera( shared_ptr<SceneInterface> s, shared_ptr<MainWindow> mw ):
		scene(s),
		focus{0, 0, 0},
		cam_angle{1, 0, 0, 0},
		cam_angle_d{1, 0, 0, 0},
		click_old{1, 0, 0, 0},
		click_new{1, 0, 0, 0},
		control{} {
	cam_aspect = 1.0;
	viewzoom = 100.0;

	// mouse action settings
	arcball_x = arcball_y = 0.0;
	arcball_radius = 1.0;
	click_x = click_y = 0;

	wnd = mw;
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
	glGetDoublev(GL_PROJECTION_MATRIX, proj_matrixd);

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
	glGetDoublev(GL_PROJECTION_MATRIX, model_matrixd);

	scene->display( shared_from_this(), tick );
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
	if (state) {
		control[0] = control[1] = control[2] = false;
		setupMatrix();
		return scene->mouseClicked( shared_from_this(), button, state, x, y );
	}

	/* controls while holding shift */
	if ((glutGetModifiers() & GLUT_ACTIVE_SHIFT) == GLUT_ACTIVE_SHIFT) {
		if (button == 0) {
			control[0] = true;
			getArc( arcball_x, arcball_y, x, y, arcball_radius, &click_new ); // initial click down
			click_old = click_new;
		}
		else if (button == 2) {
			// panning
			control[1] = true;
			click_x = x;
			click_y = y;
		}
		else if (button == 3) {
			viewzoom /= 1.05;	// scroll back
		}
		else if (button == 4) {
			viewzoom *= 1.05;	// scroll forward
		}
		return true;
	}
	else  {
		setupMatrix();
		return scene->mouseClicked( shared_from_this(), button, state, x, y );
	}
}

int Camera::mouseDragged(int x, int y) {
	if (control[0]) {
		getArc(arcball_x, arcball_y, x, y, arcball_radius, &click_new);
		cam_angle_d = click_new * click_old.multiplicativeInverse();
		click_old = click_new;
		return true;
	}
	else if (control[1]) {
		float xn = click_x - x;
		float yn = click_y - y;
		float len_sq = xn*xn + yn*yn;
		if (len_sq > 0.1) {
			float len = sqrt(len_sq);
			Vec3D add = (cam_angle.multiplicativeInverse() * Quaternion{0, xn, yn, 0} * cam_angle).vector();
			focus = focus + add * (len / arcball_radius);
			click_x = x;
			click_y = y;
		}
		return true;
	}
	else {
		setupMatrix();
		return scene->mouseDragged( shared_from_this(), x, y );
	}
}

Quaternion Camera::cameraAngle() {
	return cam_angle;
}

Vec3D Camera::unProject(int x, int y) {
	GLdouble point[3];
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
	gluUnProject(x, y, 0.99, modelview, projection, viewport, &point[0], &point[1], &point[2]);
	return Vec3D(point[0], point[1], point[2]);
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

void getUnitCircle(int arcx, int arcy, int ix, int iy, Quaternion *result) {
	float x = ix - arcx;
	float y = iy - arcy;
	float len = sqrt(x*x + y*y);
	*result = Quaternion(0, x / len, y / len, 0);
}

} /* namespace std */
