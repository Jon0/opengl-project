/*
 * Program.cpp
 *
 *  Created on: 23/09/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Program.h"

namespace std {

Program::Program():
		vert("assets/shaders/bump.vert", GL_VERTEX_SHADER),
		frag("assets/shaders/bump.frag", GL_FRAGMENT_SHADER),
		vb(15)
{
	//Create a program handle.
	programID = glCreateProgram();

	//Attach the shaders. Here, assume that fragmentHandle is a handle to a fragment shader object,
	//and that vertexHandle is a handle to a vertex shader object.
	glAttachShader(programID, vert.ShaderHandle);
	glAttachShader(programID, frag.ShaderHandle);

    //glBindAttribLocation(programID, 0, "in_Position");
    //glBindAttribLocation(programID, 1, "in_Normal");
    //glBindAttribLocation(programID, 2, "in_Color");

	//Link the program.
	glLinkProgram(programID);

	int rvalue;
	glGetProgramiv(programID, GL_LINK_STATUS, &rvalue);
	if (!rvalue) {
		fprintf(stderr, "Error in linking shader program\n");
		GLchar log[10240];
		GLsizei length;
		glGetProgramInfoLog(programID, 10239, &length, log);
		fprintf(stderr, "Linker log:\n%s\n", log);
	}
	glUseProgram (programID);




	/* texturing... */
	// TODO delete this
	diffuseTex = new Tex();
	diffuseTex->make2DTex("assets/image/wood.jpg");
	normalTex = new Tex();
	normalTex->make2DTex("assets/image/normal.jpg");


	/*
	 * set uniforms
	 */
	LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
	ModelView3x3MatrixID = glGetUniformLocation(programID, "MV3x3");
    MatrixID = glGetUniformLocation(programID, "MVP");
    ViewMatrixID = glGetUniformLocation(programID, "V");
    ModelMatrixID = glGetUniformLocation(programID, "M");

	DiffuseTextureID  = glGetUniformLocation(programID, "DiffuseTextureSampler");
	NormalTextureID  = glGetUniformLocation(programID, "NormalTextureSampler");
	SpecularTextureID  = glGetUniformLocation(programID, "SpecularTextureSampler");

	t = 0.0;

}

Program::~Program() {
	// TODO Auto-generated destructor stub
}

void Program::setup( shared_ptr<Geometry> d ) {

	// setup VBO
	d->init(&vb);
	vb.store();
}

void Program::enable() {
	/*
	 * attach buffers
	 */
	glBindBuffer( GL_ARRAY_BUFFER, vb.addr() );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vb.stride * sizeof(float), (void *)(0*4));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vb.stride * sizeof(float), (void *)(3*4));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vb.stride * sizeof(float), (void *)(6*4));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, vb.stride * sizeof(float), (void *)(9*4));
    glEnableVertexAttribArray(3);

    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, vb.stride * sizeof(float), (void *)(12*4));
    glEnableVertexAttribArray(4);

	// Bind our diffuse texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTex->getAddr());
	// Set our "DiffuseTextureSampler" sampler to user Texture Unit 0
	glUniform1i(DiffuseTextureID, 0);
	glUniform1i(SpecularTextureID, 0);

	// Bind our normal texture in Texture Unit 1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normalTex->getAddr());
	// Set our "Normal    TextureSampler" sampler to user Texture Unit 0
	glUniform1i(NormalTextureID, 1);



	// setup bump mapping
	GLfloat modelview[16];
	GLfloat projection[16];
	glGetFloatv( GL_MODELVIEW_MATRIX, modelview );
	glGetFloatv( GL_PROJECTION_MATRIX, projection );

	glm::mat4 ProjectionMatrix = glm::make_mat4(projection);
	glm::mat4 ViewMatrix = glm::make_mat4(modelview);
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	glm::mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
	glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix); // Take the upper-left part of ModelViewMatrix
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix3fv(ModelView3x3MatrixID, 1, GL_FALSE, &ModelView3x3Matrix[0][0]);
	GLfloat lightPos[] = { 7.5 * sin(t), 2.0f * 1, 7.5 * cos(t), 0.0f };
	t += 0.01;
	glUniform3f(LightID, lightPos[0], lightPos[1], lightPos[2]);




	/*
	 * enable program
	 */
	glUseProgram(programID);
}

} /* namespace std */
