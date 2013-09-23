/*
 * Program.cpp
 *
 *  Created on: 23/09/2013
 *      Author: remnanjona
 */

#include "Program.h"

namespace std {

Program::Program():
		vert("assets/shaders/test.vert", GL_VERTEX_SHADER),
		frag("assets/shaders/test.frag", GL_FRAGMENT_SHADER),
		vb(9)
{
	//Create a program handle.
	programID = glCreateProgram();

	//Attach the shaders. Here, assume that fragmentHandle is a handle to a fragment shader object,
	//and that vertexHandle is a handle to a vertex shader object.
	glAttachShader(programID, vert.ShaderHandle);
	glAttachShader(programID, frag.ShaderHandle);

    glBindAttribLocation(programID, 0, "in_Position");
    glBindAttribLocation(programID, 1, "in_Color");

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
	//glVertexPointer(3, GL_FLOAT, 9 * 4, (GLvoid *)(0*4)); //vertices
	//glNormalPointer(GL_FLOAT, 9 * 4, (GLvoid *)(3*4));
	//glTexCoordPointer(3, GL_FLOAT, 9 * 4, (GLvoid *)(6*4));
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(0*4));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3*4));
    glEnableVertexAttribArray(1);

	/*
	 * enable program
	 */
	glUseProgram(programID);
}

} /* namespace std */
