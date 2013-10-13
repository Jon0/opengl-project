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

#include "../pipeline/Step.h"
#include "../shader/ShaderStructs.h"
#include "../shader/Program.h"
#include "../shader/UniformControl.h"
#include "Light.h"

namespace std {

void display_cylinder(GLUquadric* q, float x, float y, float z, float length, float width, float spotangle);

class LightingModel:
		public Step
{
public:
	Program shadow;
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
	UniformControl<glm::mat4> modelMatrix; // TODO remove

	UniformControl<vector<GLint>> shadowMaps;
	UniformControl<vector<glm::mat4>> DepthBias;

	/*
	 * set of lights used
	 */
	vector< Light * > lights;

	/*
	 * the scene geometry
	 */
	shared_ptr<SceneInterface> scene;

	/* time */
	float t;

	LightingModel( shared_ptr<SceneInterface> si );
	virtual ~LightingModel();

	LightProperties &getLight(int);
	void updateLight(int);
	void generateShadowFBO();
	void clearDepthMap();
	void createShadow( shared_ptr<Geometry> );
	void setLight(Program &, UniformBlock<LightProperties> &);
	void drawIcons();

	virtual Program &getProgram();
	virtual void update( chrono::duration<double> );
	virtual void run( shared_ptr<ViewInterface> );
};

} /* namespace std */
#endif /* LIGHTING_MODEL_H_ */
