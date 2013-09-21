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

	/*
	 * shaders
	 */
	GLhandleARB program;
	Shader vert;
	Shader frag;

	int shadowMapWidth;
	int shadowMapHeight;

	// Hold id of the framebuffer for light POV rendering
	GLuint fboId;

	// Z values will be rendered to this texture when using fboId framebuffer
	GLuint depthTextureId;

	GLuint shadowMapUniform;

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
