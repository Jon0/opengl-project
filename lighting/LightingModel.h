/*
 * LightingModel.h
 *
 *  Created on: 21/09/2013
 *      Author: remnanjona
 */

#ifndef LIGHTINGMODEL_H_
#define LIGHTINGMODEL_H_

#include "../shader/Shader.h"
#include <GL/gl.h>

namespace std {

class LightingModel {
public:

	GLfloat lightPos[4];

	/*
	 * shaders
	 */
	GLuint program;
	Shader vert;
	Shader frag;

	int shadowMapWidth;
	int shadowMapHeight;

	// Hold id of the framebuffer for light POV rendering
	GLuint fboId;

	// Z values will be rendered to this texture when using fboId framebuffer
	GLuint depthTextureId;

	/*
	 * uniforms
	 */
	GLuint shadowMapUniform;
	GLuint LightID;
	GLuint ModelView3x3MatrixID;
    GLuint MatrixID;
    GLuint ViewMatrixID;
    GLuint ModelMatrixID;

	LightingModel();
	virtual ~LightingModel();

	void generateShadowFBO();
	void setTextureMatrix();
	void prepareShadow();
	void setLight();

	void startTranslate(float,float,float);
	void endTranslate();

};

} /* namespace std */
#endif /* LIGHTINGMODEL_H_ */
