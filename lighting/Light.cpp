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
	shadowMapWidth = 1024 * 8; //800 * 3;
	shadowMapHeight = 1024 * 8; //600 * 3;
	generateShadowFBO();

	/* main shader */
	shadowMapUniform = main.addUniform("shadowMap");
	DepthBias  = main.addUniform("DepthBiasMVP");
	LightID = main.addUniform("LightPosition_worldspace");

	/* depth shader */
	modelMatrix = shadow.addUniform("depthMVP");

	/* texture translation matrix */
	biasMatrix = glm::mat4(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
	);

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

void Light::getDepthMap() {
	position = glm::vec3( 12.5f * sin(t), 8.0f, 12.5f * cos(t) );
	t += 0.01;

	//First step: Render from the light POV to a FBO, story depth values only
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, fboId);	//Rendering offscreen
	glViewport(0, 0, shadowMapWidth, shadowMapHeight);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}



void Light::setLight() {
	// Now rendering from the camera POV, using the FBO to generate shadows
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Using the shadow shader
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, depthTextureId);
	glUniform1i(shadowMapUniform, 7);

	glUniform3f(LightID, position.x, position.y, position.z);
}

void Light::setTranslation(glm::vec3 pos) {

	// Compute the MVP matrix from the light's point of view
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-80,80,-80,80,-80,80);
	glm::mat4 depthViewMatrix = glm::lookAt(position, glm::vec3(0,0,0), glm::vec3(0,1,0));
	glm::mat4 depthModelMatrix = glm::translate(glm::mat4(1.0), pos);
	depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, &depthMVP[0][0]);

}

void Light::setTranslationB() {
	glm::mat4 depthBiasMVP = biasMatrix*depthMVP;

		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
	glUniformMatrix4fv(DepthBias, 1, GL_FALSE, &depthBiasMVP[0][0]);
}

} /* namespace std */
