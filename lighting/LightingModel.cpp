/*
 * Light.cpp
 *
 *  Created on: 25/09/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <GL/glu.h>

#include "types/Directional.h"
#include "types/Positional.h"
#include "types/Spotlight.h"
#include "LightingModel.h"

namespace std {

LightingModel::LightingModel(Program &main):
		shadow("shadow_depth"),
		modelMatrix { [](GLuint i, glm::mat4 v){ glUniformMatrix4fv(i, 1, GL_FALSE, &v[0][0]); } },
		shadowMaps { [](GLuint i, vector<GLint> v){ glUniform1iv(i, v.size(), v.data()); } },
		DepthBias { [](GLuint i, vector<glm::mat4> v){ glUniformMatrix4fv(i, v.size(), GL_FALSE, &v.data()[0][0][0]); } },
		lightUniform { main.getBlock<LightProperties>("LightProperties", 8) },
		tree { 128 }
{
	shadowMapWidth = 1024 * 4;
	shadowMapHeight = 1024 * 4;

	/*
	 * setup lights
	 */
	lights.push_back( new Positional() );
	lights.push_back( new Spotlight() );
	lights.push_back( new Directional() );
	numLights = lights.size();

	// map each light to its index
	lightUniform.assign(lights.data()[0], 0);
	lightUniform.assign(lights.data()[1], 1);
	lightUniform.assign(lights.data()[2], 2);

	shadowMaps.data.resize(numLights);
	DepthBias.data.resize(numLights);
	depthTextureId.resize(numLights);
	fboId.resize(numLights);	//main.setUniform("LightPosition_worldspace", &Positions);
	generateShadowFBO();

	/* depth shader */
	shadow.setUniform("depthMVP", &modelMatrix);

	/* main shader */
	main.setUniform("shadowMap", &shadowMaps);
	main.setUniform("DepthBiasMVP", &DepthBias);
	main.setUniform("illumination", &tree.location);

	/* texture translation matrix */
	biasMatrix = glm::mat4(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
	);
}

LightingModel::~LightingModel() {
	// TODO Auto-generated destructor stub
}

LightProperties &LightingModel::getLight(int i) {
	return lights.data()[i]->data;
}

void LightingModel::updateLight(int i) {
	lights.data()[i]->update();
}

void LightingModel::track(shared_ptr<Geometry> g) {
	tree.calc(g);
}

void LightingModel::generateShadowFBO() {
	GLenum FBOstatus;

	// Try to use a texture depth component
	glGenTextures(numLights, depthTextureId.data());
	for (unsigned int i = 0; i < numLights; ++i) {
		glBindTexture(GL_TEXTURE_2D, depthTextureId.data()[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0,
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

		// won't bind a color texture with the currently bound FBO
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

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

void LightingModel::clearDepthMap() {
	//First step: Render from the light POV to a FBO, story depth values only
	shadow.enable();
	for (unsigned int i = 0; i < numLights; ++i) {
		glBindFramebuffer(GL_FRAMEBUFFER_EXT, fboId.data()[i]);	//Rendering offscreen
		glViewport(0, 0, shadowMapWidth, shadowMapHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
}

void LightingModel::createShadow( shared_ptr<Geometry> g ) {
	// Compute the MVP matrix from the light's point of view
	for (unsigned int i = 0; i < numLights; ++i) {
		glBindFramebuffer(GL_FRAMEBUFFER_EXT, fboId.data()[i]);	//Rendering offscreen
		modelMatrix.setV( lights.data()[i]->getTransform() * g->transform() );
		g->draw();
	}
}



void LightingModel::setLight() {
	// Now rendering from the camera POV, using the FBO to generate shadows
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	/*
	 * bind shadow maps
	 */
	for (unsigned int i = 0; i < numLights; ++i) {
		glActiveTexture(GL_TEXTURE5 + i);
		glBindTexture(GL_TEXTURE_2D, depthTextureId.data()[i]);
		shadowMaps.data.data()[i] = 5 + i;
	}
	shadowMaps.forceUpdate();

	/*
	 * bind illumination
	 */
	tree.enable(5 + numLights);

	for (unsigned int i = 0; i < numLights; ++i) {
			DepthBias.data.data()[i] = biasMatrix * lights.data()[i]->getTransform();
	}
	DepthBias.forceUpdate();
}

void LightingModel::drawIcons() {
	glDisable(GL_CULL_FACE);
	GLUquadric* quad = gluNewQuadric();
	gluQuadricDrawStyle(quad, GLU_LINE);
	for (UBO<LightProperties> *l :lights) {
		glm::vec4 &cl = l->data.color;
		glColor3f(cl.x, cl.y, cl.z);
		glm::vec4 &pos = l->data.position;
		if (l->data.spotlight > 0) {
			glm::vec4 &spot = l->data.direction;
			glm::vec4 dir = glm::normalize(spot - pos);
			glPushMatrix();
			glTranslatef(pos.x, pos.y, pos.z);
			display_cylinder(quad, dir.x, dir.y, dir.z, 1.0, 0.0, l->data.spotlight);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(spot.x, spot.y, spot.z);
			gluSphere(quad, 0.50, 4, 4);
			glPopMatrix();
		}
		else if (pos.w < 0.1) {
			glPushMatrix();
			glTranslatef(pos.x, pos.y, pos.z);
			glm::vec4 dir = glm::normalize(-pos);
			display_cylinder(quad, dir.x, dir.y, dir.z, 1.5, 0.33, 1.0);
			glPopMatrix();
		}
		else {
			glPushMatrix();
			glTranslatef(pos.x, pos.y, pos.z);
			gluSphere(quad, 0.50, 4, 4);
			glPopMatrix();
		}
	}
}

void display_cylinder(GLUquadric* q, float x, float y, float z, float length, float width, float spotangle) {
	const float rad_to_deg = 360.0/(2 * M_PI);
	Vec3D z_vec, d_vec;
	z_vec.v[0] = 0;	z_vec.v[1] = 0;	z_vec.v[2] = 1;
	d_vec.v[0] = x;	d_vec.v[1] = y;	d_vec.v[2] = z;
	Vec3D *a = &z_vec, *b = &d_vec;
	*a = a->crossProduct(*b);

	// dot product simplifies to z axis
	float angle = rad_to_deg * acos(z);
	float d = sqrt(a->v[0]*a->v[0] + a->v[1]*a->v[1] + a->v[2]*a->v[2]);

	// draw cylinder, rotated in correct direction
	glPushMatrix();

	if (d > 0) {
		glRotatef(angle, a->v[0], a->v[1], a->v[2]);
	}
	gluCylinder(q, width, width + M_PI*length*(1-spotangle), length, 8, 3);
	glPopMatrix();
}

} /* namespace std */
