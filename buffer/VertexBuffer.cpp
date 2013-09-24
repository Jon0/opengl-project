/*
 * VertexBuffer.cpp
 *
 *  Created on: 30/04/2013
 *      Author: remnanjona
 */

#include <stdio.h>
#include <iostream>
#include "VertexBuffer.h"

namespace std {

VertexBuffer::VertexBuffer(int s): stride(s) {
	vb = -1;
}

GLuint VertexBuffer::addr() {
	return vb;
}

long VertexBuffer::add( vector<GVertex> &add ) {
	long start = vert.size();
	for (vector<GVertex>::iterator i = add.begin(); i < add.end(); ++i) {
		vert.push_back(*i);
	}
	return start;
}

void VertexBuffer::store() {
	GLfloat *vertices = new GLfloat[vert.size() * stride];

	int offset = 0;
	for (vector<GVertex>::iterator i = vert.begin(); i < vert.end(); ++i) {
		(*i).toArray( vertices, offset );
		//for (int k = 0; k < stride; ++k) cout << vertices[offset+k] << ", ";
		//cout << endl;
		offset += stride;
	}

	GLuint vao;

	/* Allocate and assign a Vertex Array Object to our handle */
	glGenVertexArrays(1, &vao);

	/* Bind our Vertex Array Object as the current used object */
	glBindVertexArray(vao);

	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, 4*vert.size()*stride, vertices, GL_STATIC_DRAW);

	delete vertices;
}

VertexBuffer::~VertexBuffer() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
