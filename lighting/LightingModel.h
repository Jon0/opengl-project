/*
 * LightingModel.h
 *
 *  Created on: 25/09/2013
 *      Author: remnanjona
 */

#ifndef LIGHTING_MODEL_H_
#define LIGHTING_MODEL_H_

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/gl.h>

#include "../shader/ShaderStructs.h"
#include "../shader/Program.h"
#include "../shader/UniformControl.h"

namespace std {

class LightingModel {
public:
	int shadowMapWidth;
	int shadowMapHeight;
	unsigned int numLights;
	GLuint test;

	// Hold id of the framebuffer for light POV rendering
	vector<GLuint> fboId;

	// Z values will be rendered to this texture when using fboId framebuffer
	vector<GLuint> depthTextureId;

	/* matrix */
	glm::mat4 biasMatrix;

	/*
	 * uniforms
	 */
	UniformControl<glm::mat4> modelMatrix;

	UniformControl<vector<GLint>> shadowMaps;
	UniformControl<vector<glm::mat4>> DepthBias;

	UniformBlock<LightProperties> lightUniform;
	vector< UBO<LightProperties> > lights;

	LightingModel(Program &shadow, Program &);
	virtual ~LightingModel();

	LightProperties &getLight(int);
	void updateLight(int);
	void generateShadowFBO();
	void clearDepthMap();
	void createShadow( shared_ptr<Geometry> );
	void setLight();
	void setTransform(glm::mat4);
	void drawIcons();
};

} /* namespace std */
#endif /* LIGHTING_MODEL_H_ */
