/*
 * Program.cpp
 *
 *  Created on: 23/09/2013
 *      Author: remnanjona
 */

#include <iostream>
#include "Program.h"

namespace std {

Program::Program():
		vert("assets/shaders/test.vert", GL_VERTEX_SHADER),
		frag("assets/shaders/test.frag", GL_FRAGMENT_SHADER),
		vb(9)
{
	programID = 0;
}

Program::~Program() {
	// TODO Auto-generated destructor stub
}

void Program::setup( shared_ptr<Geometry> d ) {
	//Create a program handle.
	programID = glCreateProgram();

	//Attach the shaders. Here, assume that fragmentHandle is a handle to a fragment shader object,
	//and that vertexHandle is a handle to a vertex shader object.
	glAttachShader(programID, vert.ShaderHandle);
	glAttachShader(programID, frag.ShaderHandle);

    glBindAttribLocation(programID, 0, "in_Position");
    glBindAttribLocation(programID, 1, "in_Normal");
    glBindAttribLocation(programID, 2, "in_Color");

	//Link the program.
	glLinkProgram(programID);

	int rvalue;
	glGetProgramiv(programID, GL_LINK_STATUS, &rvalue);
	if (!rvalue) {
		fprintf(stderr, "Error in linking compute shader program\n");
		GLchar log[10240];
		GLsizei length;
		glGetProgramInfoLog(programID, 10239, &length, log);
		fprintf(stderr, "Linker log:\n%s\n", log);
		exit(41);
	}
	glUseProgram (programID);

	// setup VBO
	d->init(&vb);
	vb.store();
}

void Program::enable() {
	/*
	 * attach buffers
	 */
	glBindBuffer( GL_ARRAY_BUFFER, vb.addr() );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(0*4));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3*4));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(6*4));
    glEnableVertexAttribArray(2);

	/*
	 * enable program
	 */
	glUseProgram(programID);
}

} /* namespace std */
