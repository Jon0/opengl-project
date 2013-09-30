/*
 * Light.cpp
 *
 *  Created on: 25/09/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <GL/glu.h>

#include "LightingModel.h"

namespace std {

LightingModel::LightingModel(Program &shadow, Program &main):
		modelMatrix { [](GLuint i, glm::mat4 v){ glUniformMatrix4fv(i, 1, GL_FALSE, &v[0][0]); } },
		shadowMaps { [](GLuint i, vector<GLint> v){ glUniform1iv(i, v.size(), v.data()); } },
		DepthBias { [](GLuint i, vector<glm::mat4> v){ glUniformMatrix4fv(i, v.size(), GL_FALSE, &v.data()[0][0][0]); } },
		//Positions { [](GLuint i, vector<glm::vec4> v){ glUniform4fv(i, v.size(), &v.data()[0][0]); } },
		lightUniform { main.getBlock<LightProperties>("LightProperties", 8) }
{
	shadowMapWidth = 1024 * 8; //800 * 3;
	shadowMapHeight = 1024 * 8; //600 * 3;

	//char data[48];
	//memcpy(&data[0], &glm::vec4(7.5, 2.0, 7.5, 1.0)[0], 16);
	//memcpy(&data[16], &glm::vec4(1.0, 1.0, 0.0, 1.0)[0], 16);


	//char data1[48];
	//memcpy(&data1[0], &glm::vec4(-0.5, 2.0, -2.5, 1.0)[0], 16);
	//memcpy(&data1[16], &glm::vec4(0.0, 0.0, 1.0, 1.0)[0], 16);
	//data[16] = glm::vec4(7.5, 2.0, 7.5, 1.0);

	//test = lights.getNewBuffer(data, 1);
	//lightProperties1.getNewBuffer(data1, 2);

	/*
	 * setup lights
	 */
	lights.push_back( UBO<LightProperties>{ 1 } );
	lights.push_back( UBO<LightProperties>{ 2 } );
	lights.push_back( UBO<LightProperties>{ 3 } );


	lightUniform.assign(&lights.data()[0], 0);
	lightUniform.assign(&lights.data()[1], 1);
	lightUniform.assign(&lights.data()[2], 2);

	lights.data()[0].data.position = glm::vec4(7.5, 2.0, 7.5, 1.0);
	lights.data()[0].data.color = glm::vec4(0.9, 0.9, 0.9, 1.0);
	lights.data()[0].update();

	lights.data()[1].data.position = glm::vec4(-0.5, 10.0, -9.5, 1.0);
	lights.data()[1].data.color = glm::vec4(0.9, 0.3, 0.9, 1.0);
	lights.data()[1].update();

	numLights = 2;


	//Positions.data.push_back( glm::vec4(7.5, 2.0, 7.5, 1.0) );
	//Positions.data.push_back( glm::vec4(-0.5, 15.0, -2.5, 1.0) );


	shadowMaps.data.resize(numLights);
	DepthBias.data.resize(numLights);
	depthTextureId.resize(numLights);
	fboId.resize(numLights);
	generateShadowFBO();

	/* depth shader */
	shadow.setUniform("depthMVP", &modelMatrix);

	/* main shader */
	main.setUniform("shadowMap", &shadowMaps);
	main.setUniform("DepthBiasMVP", &DepthBias);
	//main.setUniform("LightPosition_worldspace", &Positions);

	/* texture translation matrix */
	biasMatrix = glm::mat4(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
	);

	t = 0.0;
}

LightingModel::~LightingModel() {
	// TODO Auto-generated destructor stub
}

void LightingModel::generateShadowFBO() {
	GLenum FBOstatus;

	// Try to use a texture depth component

	glGenTextures(numLights, depthTextureId.data());
	for (unsigned int i = 0; i < numLights; ++i) {
		glBindTexture(GL_TEXTURE_2D, depthTextureId.data()[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, shadowMapWidth, shadowMapHeight, 0,
				GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	// create a framebuffer object
	glGenFramebuffers(numLights, fboId.data());
	for (unsigned int i = 0; i < numLights; ++i) {
		glBindFramebuffer(GL_FRAMEBUFFER, fboId.data()[i]);

		// Instruct openGL that we won't bind a color texture with the currently bound FBO
		glDrawBuffer(GL_NONE);
		//glReadBuffer(GL_NONE);

		// attach the texture to FBO depth attachment point
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTextureId.data()[i], 0);

		// check FBO status
		FBOstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (FBOstatus != GL_FRAMEBUFFER_COMPLETE)
			printf("GL_FRAMEBUFFER_COMPLETE failed, CANNOT use FBO\n");
	}

	// switch back to window-system-provided framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void LightingModel::getDepthMap() {
	lights.data()[0].data.position = glm::vec4( 12.5f * sin(t), 8.0f, 12.5f * cos(t), 1.0 );
	lights.data()[0].update();
	t += 0.01;

	//First step: Render from the light POV to a FBO, story depth values only
	for (unsigned int i = 0; i < numLights; ++i) {
		glBindFramebuffer(GL_FRAMEBUFFER_EXT, fboId.data()[i]);	//Rendering offscreen
		glViewport(0, 0, shadowMapWidth, shadowMapHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);


}

void LightingModel::getShadow( shared_ptr<Geometry> g ) {
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-80,80,-80,80,-80,80);

	// Compute the MVP matrix from the light's point of view
	for (unsigned int i = 0; i < numLights; ++i) {
		glBindFramebuffer(GL_FRAMEBUFFER_EXT, fboId.data()[i]);	//Rendering offscreen
		glm::mat4 depthViewMatrix = glm::lookAt(glm::vec3(lights.data()[i].data.position), glm::vec3(0,0,0), glm::vec3(0,1,0));
		glm::mat4 depthModelMatrix = g->transform();
		modelMatrix.setV( depthProjectionMatrix * depthViewMatrix * depthModelMatrix );
		g->draw();
	}
}



void LightingModel::setLight() {
	// Now rendering from the camera POV, using the FBO to generate shadows
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	for (unsigned int i = 0; i < numLights; ++i) {
		glActiveTexture(GL_TEXTURE5 + i);
		glBindTexture(GL_TEXTURE_2D, depthTextureId.data()[i]);
		shadowMaps.data.data()[i] = 5 + i;
	}
	shadowMaps.forceUpdate();
}

void LightingModel::setTransform(glm::mat4 t) {
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-80,80,-80,80,-80,80);

	// Compute the MVP matrix from the light's point of view
	for (unsigned int i = 0; i < numLights; ++i) {
		glm::mat4 depthViewMatrix = glm::lookAt(glm::vec3(lights.data()[i].data.position), glm::vec3(0,0,0), glm::vec3(0,1,0));
		modelMatrix.setV(depthProjectionMatrix * depthViewMatrix * t);
		DepthBias.data.data()[i] = biasMatrix * modelMatrix.getV();
	}
	DepthBias.forceUpdate();
}

} /* namespace std */
