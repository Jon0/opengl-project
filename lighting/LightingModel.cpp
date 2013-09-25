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
		vert("shader/shadow.vert", GL_VERTEX_SHADER),
		frag("shader/shadow.frag", GL_FRAGMENT_SHADER) {

	shadowMapWidth = 800 * 3;
	shadowMapHeight = 600 * 3;
	//generateShadowFBO();


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







} /* namespace std */
