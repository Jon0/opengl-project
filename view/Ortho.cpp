/*
 * Ortho.cpp
 *
 *  Created on: 26/08/2013
 *      Author: remnanjona
 */

#include <string.h>
#include <GL/glut.h>
#include "../math/Quaternion.h"
#include "../scene/SceneInterface.h"
#include "../window/MainWindow.h"
#include "Ortho.h"

namespace std {

Ortho::Ortho( shared_ptr<SceneInterface> s ): scene(s) {
	view_width = 1;
	view_height = 1;
}

Ortho::~Ortho() {}

void Ortho::setView( chrono::duration<double> tick ) {
	glUseProgram(0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, view_width, 0.0, view_height, -50.0, 50.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw scene
	scene->displayUI();
}

void Ortho::resize(int x, int y) {
	view_width = x;
	view_height = y;
}

void Ortho::keyPressed(unsigned char c) {
	if (c == '\r') {
		scene->messageSent(message);
		message.clear();
	}
	else {
		message += c;	// string append
	}
}

int Ortho::mouseClicked(int button, int state, int x, int y) {
	return scene->mouseClicked( shared_from_this(), button, state, x, y );
}

int Ortho::mouseDragged(int x, int y) {
	return scene->mouseDragged( shared_from_this(), x, y );
}

glm::quat Ortho::cameraAngle() {
	glm::quat r(1, 0, 0, 0);
	return r;
}

glm::vec3 Ortho::project(const glm::vec3 &v) {
	return v;
}

glm::vec3 Ortho::unProject(int x, int y) {
	GLdouble point[3];
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
	gluUnProject(x, y, 0, modelview, projection, viewport, &point[0], &point[1], &point[2]);
	return glm::vec3(point[0], point[1], point[2]);
}

glm::mat4 Ortho::viewMatrix() {
	return glm::mat4(1.0);
}

glm::mat4 Ortho::projectionMatrix() {
	return glm::mat4(1.0);
}

UBO<CameraProperties> *Ortho::properties() {
	return &ortho_properties;
}

void drawString(string message, float x, float y) {
	/* translate and draw text */
	glPushMatrix();
	glTranslatef(x, y, 0);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(0.0, 0.0);
	const char *str = message.c_str();
	int len = (int) strlen(str);
	void *font = GLUT_BITMAP_HELVETICA_12;
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(font, str[i]);
	}
	glPopMatrix();
}

} /* namespace std */
