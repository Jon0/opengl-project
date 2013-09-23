/*
 * LightingModel.cpp
 *
 *  Created on: 21/09/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "LightingModel.h"

namespace std {

LightingModel::LightingModel():
		lightPos{ -7.5f * 10, 2.0f * 10, -6.5f * 10, 0.0f },
		vert("shader/bump.vert", GL_VERTEX_SHADER),
		frag("shader/bump.frag", GL_FRAGMENT_SHADER) {

	shadowMapWidth = 800 * 3;
	shadowMapHeight = 600 * 3;
	generateShadowFBO();


	//Create a program handle.
	program = glCreateProgram();

	//Attach the shaders. Here, assume that fragmentHandle is a handle to a fragment shader object,
	//and that vertexHandle is a handle to a vertex shader object.
	glAttachShader(program, vert.ShaderHandle);
	glAttachShader(program, frag.ShaderHandle);

	//Link the program.
	glLinkProgram(program);

	/*
	 * set uniforms
	 */
	shadowMapUniform = glGetUniformLocation(program,"ShadowMap");
	LightID = glGetUniformLocation(program, "LightPosition_worldspace");
	ModelView3x3MatrixID = glGetUniformLocation(program, "MV3x3");
    MatrixID = glGetUniformLocation(program, "MVP");
    ViewMatrixID = glGetUniformLocation(program, "V");
    ModelMatrixID = glGetUniformLocation(program, "M");


}

LightingModel::~LightingModel() {
	// TODO Auto-generated destructor stub
}

void LightingModel::generateShadowFBO() {
	GLenum FBOstatus;

	// Try to use a texture depth component
	glGenTextures(1, &depthTextureId);
	glBindTexture(GL_TEXTURE_2D, depthTextureId);

	// GL_LINEAR does not make sense for depth texture. However, next tutorial shows usage of GL_LINEAR and PCF
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Remove artifact on the edges of the shadowmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// No need to force GL_DEPTH_COMPONENT24, drivers usually give you the max precision if available
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth,
			shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// create a framebuffer object
	glGenFramebuffersEXT(1, &fboId);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);

	// Instruct openGL that we won't bind a color texture with the currently bound FBO
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// attach the texture to FBO depth attachment point
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,
			GL_TEXTURE_2D, depthTextureId, 0);

	// check FBO status
	FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if (FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
		printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");

	// switch back to window-system-provided framebuffer
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void LightingModel::setTextureMatrix() {
	static double modelView[16];
	static double projection[16];

	// Moving from unit cube [-1,1] to [0,1]
	const GLdouble bias[16] = {
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0 };

	// Grab modelview and transformation matrices
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	glMatrixMode(GL_TEXTURE);
	glActiveTexture(GL_TEXTURE7);

	glLoadIdentity();
	glLoadMatrixd(bias);

	// concatating all matrices into one.
	glMultMatrixd(projection);
	glMultMatrixd(modelView);

	// Go back to normal matrix mode
	glMatrixMode(GL_MODELVIEW);
}

// During translation, we also have to maintain the GL_TEXTURE8, used in the shadow shader
// to determine if a vertex is in the shadow.
void LightingModel::startTranslate(float x,float y,float z)
{
	glPushMatrix();
	glTranslatef(x,y,z);

	glMatrixMode(GL_TEXTURE);
	glActiveTexture(GL_TEXTURE7);
	glPushMatrix();
	glTranslatef(x,y,z);
}

void LightingModel::endTranslate() {
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void LightingModel::prepareShadow() {
	glEnable(GL_CULL_FACE);

	//First step: Render from the light POV to a FBO, story depth values only
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);	//Rendering offscreen

	//Using the fixed pipeline to render to the depthbuffer
	glUseProgram(0);

	// In the case we render the shadowmap to a higher resolution, the viewport must be modified accordingly.
	glViewport(0, 0, shadowMapWidth, shadowMapHeight);

	// Clear previous frame values
	glClear( GL_DEPTH_BUFFER_BIT);

	//Disable color rendering, we only want to write to the Z-Buffer
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 800.0/600.0, 10.0, 40000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-7.5f * 3, 2.0f * 3, -6.5f * 3, 0,0,0, 0,1,0);

	// Culling switching, rendering only backface, this is done to avoid self-shadowing
	glCullFace(GL_FRONT);
}

void LightingModel::setLight() {
	// set lighting
	GLfloat lightPos[] = { -7.5f * 1, 2.0f * 1, -6.5f * 1, 0.0f };
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
	glEnable(GL_LIGHT0);

	glUseProgram(program);

	//Using the shadow shader
	//glUniform1i(shadowMapUniform, 7);
	//glActiveTexture(GL_TEXTURE7);
	//glBindTexture(GL_TEXTURE_2D, depthTextureId);

	// setup bump mapping
	GLfloat modelview[16];
	GLfloat projection[16];
	glGetFloatv( GL_MODELVIEW_MATRIX, modelview );
	glGetFloatv( GL_PROJECTION_MATRIX, projection );

	glm::mat4 ProjectionMatrix = glm::make_mat4(projection);
	glm::mat4 ViewMatrix = glm::make_mat4(modelview);
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	glm::mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
	glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix); // Take the upper-left part of ModelViewMatrix
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix3fv(ModelView3x3MatrixID, 1, GL_FALSE, &ModelView3x3Matrix[0][0]);
	glUniform3f(LightID, lightPos[0], lightPos[1], lightPos[2]);
}

} /* namespace std */
