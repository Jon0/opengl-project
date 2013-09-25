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

Program::Program(string file):
		vert("assets/shaders/"+file+".vert", GL_VERTEX_SHADER),
		frag("assets/shaders/"+file+".frag", GL_FRAGMENT_SHADER)
{
	//Create a program handle.
	programID = glCreateProgram();

	//Attach the shaders. Here, assume that fragmentHandle is a handle to a fragment shader object,
	//and that vertexHandle is a handle to a vertex shader object.
	glAttachShader(programID, vert.ShaderHandle);
	glAttachShader(programID, frag.ShaderHandle);

	glBindAttribLocation(programID, 0, "vertexPosition_modelspace");
	glBindAttribLocation(programID, 1, "vertexUV");
	glBindAttribLocation(programID, 2, "vertexNormal_modelspace");
	glBindAttribLocation(programID, 3, "vertexTangent_modelspace");
    glBindAttribLocation(programID, 4, "vertexBitangent_modelspace");
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
}

Program::~Program() {
	// TODO Auto-generated destructor stub
}

GLuint Program::addUniform(string name) {
	GLuint id = glGetUniformLocation(programID, name.c_str());
	uniform[name] = id;
	return id;
}

GLuint Program::getUniform(string name) {
	return uniform[name];
}

void Program::setup( shared_ptr<Geometry> d ) {


}

// TODO ???
void Program::setTranslation() {

}


void Program::enable() {
	/*
	 * enable program
	 */
	glUseProgram(programID);
}

} /* namespace std */
