/*
 * Program.cpp
 *
 *  Created on: 23/09/2013
 *      Author: remnanjona
 */

#include "Program.h"

namespace std {

Program::Program():
		vert("assets/shaders/phong.vert", GL_VERTEX_SHADER),
		frag("assets/shaders/phong.frag", GL_FRAGMENT_SHADER),
		vb(9)
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
}

Program::~Program() {
	// TODO Auto-generated destructor stub
}

void Program::setup( shared_ptr<Geometry> d ) {
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

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(6*4));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3*4));
    glEnableVertexAttribArray(2);

	/*
	 * enable program
	 */
	glUseProgram(programID);
}

} /* namespace std */
