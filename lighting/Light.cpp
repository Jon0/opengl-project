/*
 * Light.cpp
 *
 *  Created on: 25/09/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <GL/glu.h>

#include "Light.h"

namespace std {

Light::Light(Program &shadow, Program &main):
		position(7.5, 2.0, 7.5)
{
	shadowMapWidth = 1024 * 4; //800 * 3;
	shadowMapHeight = 1024 * 4; //600 * 3;
	generateShadowFBO();

	/* main shader */
	shadowMapUniform = main.addUniform("shadowMap");
	DepthBias  = main.addUniform("DepthBiasMVP");
	LightID = main.addUniform("LightPosition_worldspace");

	/* depth shader */
	modelMatrix = shadow.addUniform("depthMVP");
	cout << modelMatrix << endl;

	t = 0.0;
}

Light::~Light() {
	// TODO Auto-generated destructor stub
}

void Light::generateShadowFBO() {
	GLenum FBOstatus;

	// Try to use a texture depth component
	glGenTextures(1, &depthTextureId);
	glBindTexture(GL_TEXTURE_2D, depthTextureId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, shadowMapWidth, shadowMapHeight, 0,
			GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	glBindTexture(GL_TEXTURE_2D, 0);

	// create a framebuffer object
	glGenFramebuffers(1, &fboId);
	glBindFramebuffer(GL_FRAMEBUFFER, fboId);

	// Instruct openGL that we won't bind a color texture with the currently bound FBO
	glDrawBuffer(GL_NONE);
	//glReadBuffer(GL_NONE);

	// attach the texture to FBO depth attachment point
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTextureId, 0);

	// check FBO status
	FBOstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (FBOstatus != GL_FRAMEBUFFER_COMPLETE)
		printf("GL_FRAMEBUFFER_COMPLETE failed, CANNOT use FBO\n");

	// switch back to window-system-provided framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Light::setTextureMatrix() {
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
void Light::startTranslate(float x,float y,float z)
{
	glPushMatrix();
	glTranslatef(x,y,z);

	glMatrixMode(GL_TEXTURE);
	glActiveTexture(GL_TEXTURE7);
	glPushMatrix();
	glTranslatef(x,y,z);
}

void Light::endTranslate() {
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Light::prepareShadow() {
	//Using the fixed pipeline to render to the depthbuffer
	glUseProgram(0);

	glEnable(GL_CULL_FACE);

	//First step: Render from the light POV to a FBO, story depth values only
	//glBindFramebuffer(GL_FRAMEBUFFER, fboId);	//Rendering offscreen

	// In the case we render the shadowmap to a higher resolution, the viewport must be modified accordingly.
	// glViewport(0, 0, shadowMapWidth, shadowMapHeight);

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

void Light::getDepthMap() {
	position = glm::vec3( 12.5f * sin(t), 8.0f, 12.5f * cos(t) );
	t += 0.01;

	//First step: Render from the light POV to a FBO, story depth values only
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, fboId);	//Rendering offscreen
	glViewport(0, 0, shadowMapWidth, shadowMapHeight);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	 // Compute the MVP matrix from the light's point of view
	 glm::mat4 depthProjectionMatrix = glm::ortho<float>(-80,80,-80,80,-80,80);
	 glm::mat4 depthViewMatrix = glm::lookAt(position, glm::vec3(0,0,0), glm::vec3(0,1,0));
	 glm::mat4 depthModelMatrix = glm::mat4(1.0);
	 depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

	 // Send our transformation to the currently bound shader,
	 // in the "MVP" uniform
	 glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, &depthMVP[0][0]);
}



void Light::setLight() {
	// Now rendering from the camera POV, using the FBO to generate shadows
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	glViewport(0, 0, 800, 600);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Using the shadow shader
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, depthTextureId);
	glUniform1i(shadowMapUniform, 7);

	glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
	);
	glm::mat4 depthBiasMVP = biasMatrix*depthMVP;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(DepthBias, 1, GL_FALSE, &depthBiasMVP[0][0]);
	glUniform3f(LightID, position.x, position.y, position.z);

}

} /* namespace std */
