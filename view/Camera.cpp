/*
 * Camera.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <math.h>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

namespace std {

Camera::Camera( shared_ptr<SceneInterface> s, shared_ptr<MainWindow> mw ):
		scene(s),
		focus{0, 0, 0},
		cam_angle{1, 0, 0, 0},
		cam_angle_d{1, 0, 0, 0},
		click_old{1, 0, 0, 0},
		click_new{1, 0, 0, 0},
		control{}

{
	cam_aspect = 1.0;
	viewzoom = 10.0;

	// mouse action settings
	arcball_x = arcball_y = 0.0;
	arcball_radius = 1.0;
	click_x = click_y = 0;
	windowwidth = windowheight = 1;

	wnd = mw;
}

Camera::~Camera() {}

void Camera::setView( chrono::duration<double> tick ) {
	cam_angle = cam_angle_d * cam_angle;
	//cam_angle.rotate( cam_angle_d );
	cam_angle_d = glm::slerp( glm::quat(), cam_angle_d, ( 1 - (float)tick.count() * 10 ) );

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, cam_aspect, 1.0, 1000.0);
	glGetFloatv(GL_PROJECTION_MATRIX, proj_matrix);
	glGetDoublev(GL_PROJECTION_MATRIX, proj_matrixd);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// setup camera position
	glPushMatrix();
	glTranslatef(0.0, 0.0, -viewzoom);
	//cam_angle.toMatrix(temp_matrix);
	glMultMatrixf( &glm::mat4_cast(cam_angle)[0][0] );

	float x = focus.x, y = focus.y, z = focus.z;
	gluLookAt(x, y, z, x, y, z - viewzoom, 0.0, 1.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, model_matrix);
	glGetDoublev(GL_PROJECTION_MATRIX, model_matrixd);

	// get this first
	GLfloat modelviewf[16];
	GLfloat projectionf[16];
	glGetFloatv( GL_MODELVIEW_MATRIX, modelviewf );
	glGetFloatv( GL_PROJECTION_MATRIX, projectionf );


	properties.data.P = glm::make_mat4(projectionf);
	properties.data.V = glm::make_mat4(modelviewf);
	properties.data.M = glm::mat4(1.0);
	properties.update();

	//projection.setV( glm::make_mat4(projectionf) );
	//view.setV( glm::make_mat4(modelviewf) );
	//VP.setV( projection.getV() * view.getV() );

	scene->prepare();

	glBindFramebuffer(GL_FRAMEBUFFER,0);
	glViewport(0, 0, windowwidth, windowheight);

	scene->display( shared_from_this(), tick );
	glPopMatrix();
}

void Camera::resize(int x, int y) {
	windowwidth = x;
	windowheight = y;
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
			getArc( arcball_x, arcball_y, x, y, arcball_radius, click_new ); // initial click down
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
		getArc(arcball_x, arcball_y, x, y, arcball_radius, click_new);
		// cam_angle_d = click_new * click_old.multiplicativeInverse();
		glm::quat q = cam_angle_d = click_new * glm::inverse(click_old);
		cam_angle_d = q * cam_angle_d;
		click_old = click_new;
		return true;
	}
	else if (control[1]) {
		float xn = click_x - x;
		float yn = click_y - y;
		float len_sq = xn*xn + yn*yn;
		if (len_sq > 0.1) {
			float len = sqrt(len_sq);
			glm::vec3 add = glm::axis( glm::inverse(cam_angle) * glm::quat(0, xn, yn, 0) * cam_angle );
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

glm::quat Camera::cameraAngle() {
	return cam_angle;
}

glm::vec2 Camera::project(glm::vec3 v) {
	//properties.data.P.
	return properties.data.P * properties.data.V * glm::vec4(v.x, v.y, v.z, 1.0);

	glm::project()
	//return glm::vec2(0, 0); // TODO stuff
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

glm::mat4 Camera::viewMatrix() {
	return properties.data.V;
}

glm::mat4 Camera::projectionMatrix() {
	return properties.data.P;
}


void Camera::setupMatrix() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(proj_matrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(model_matrix);
}

void getArc(int arcx, int arcy, int ix, int iy, float rad, glm::quat &result) {
	float x = (ix - arcx) / rad;
	float y = (iy - arcy) / rad;

	// check click is inside the arcball radius
	if (x*x + y*y < 1.0) {
		float z = sqrt(1 - (x*x + y*y));
		result = glm::quat(0, x, y, z);
	}
	else {
		float len = sqrt(x*x + y*y);
		result = glm::quat(0, x / len, y / len, 0);
	}
}

void getUnitCircle(int arcx, int arcy, int ix, int iy, glm::quat &result) {
	float x = ix - arcx;
	float y = iy - arcy;
	float len = sqrt(x*x + y*y);
	result = glm::quat(0, x / len, y / len, 0);
}

} /* namespace std */
