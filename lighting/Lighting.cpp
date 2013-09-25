/*
 * Lighting.cpp
 *
 *  Created on: 24/09/2013
 *      Author: remnanjona
 */

#include <GL/gl.h>
#include "Lighting.h"

namespace std {

Lighting::Lighting() {
	// TODO Auto-generated constructor stub

}

Lighting::~Lighting() {
	// TODO Auto-generated destructor stub
}

void Lighting::setup() {
	// set lighting
	GLfloat lightPos[] = { -7.5f * 100, 2.0f * 100, -6.5f * 100, 0.0f };
	GLfloat lightColorDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat lightColorAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColorDiffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightColorAmbient);

	GLfloat material_diffuse[] = { 0.45f, 0.45f, 0.45f, 1.0f };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material_diffuse);
	glEnable (GL_LIGHT0);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glColor3f(1.0f,1.0f,1.0f);
}

} /* namespace std */
