/*
 * Light.h
 *
 *  Created on: 25/09/2013
 *      Author: remnanjona
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/gl.h>

#include "../shader/Program.h"

namespace std {

class Light {
public:

	glm::vec3 position;

	int shadowMapWidth;
	int shadowMapHeight;

	// Hold id of the framebuffer for light POV rendering
	GLuint fboId;

	// Z values will be rendered to this texture when using fboId framebuffer
	GLuint depthTextureId;

	/* matrix */
	glm::mat4 depthMVP;

	glm::mat4 biasMatrix;

	/*
	 * uniforms
	 */
	GLuint shadowMapUniform;
	GLuint modelMatrix;
	GLuint DepthBias;
	GLuint LightID;
	float t;

	Light(Program &shadow, Program &);
	virtual ~Light();

	void generateShadowFBO();
	void getDepthMap();
	void getShadow( shared_ptr<Geometry> );
	void setLight();
	void setTranslation(glm::vec3 pos);
	void setTranslationB();
};

} /* namespace std */
#endif /* LIGHT_H_ */
