/*
 * Cube.cpp
 *
 *  Created on: 11/05/2013
 *      Author: remnanjona
 */

#include <GL/glut.h>
#include "Cube.h"

namespace std {

Cube::Cube(float s) {
	size = s;
	index = -1;
	indices = NULL;
}

void Cube::init(VertexBuffer *vb) {
	vector<GVertex> verts;
	verts.push_back({-size,-size,-size, -0.577,-0.577,-0.577, 1,1,1});
	verts.push_back({size,-size,-size, 0.577,-0.577,-0.577, -1,1,1});
	verts.push_back({size,-size,size, 0.577,-0.577,0.577, -1,1,-1});
	verts.push_back({-size,-size,size, -0.577,-0.577,0.577, 1,1,-1});
	verts.push_back({-size,size,-size, -0.577,0.577,-0.577, 1,-1,1});
	verts.push_back({size,size,-size, 0.577,0.577,-0.577, -1,-1,1});
	verts.push_back({size,size,size, 0.577,0.577,0.577, -1,-1,-1});
	verts.push_back({-size,size,size, -0.577,0.577,0.577, 1,-1,-1});
	index = vb->add(verts);

	indices = new GLuint[18];
	indices[0] = index + 6;
	indices[1] = index + 2;
	indices[2] = index + 7;
	indices[3] = index + 3;
	indices[4] = index + 4;
	indices[5] = index + 0;

	indices[6] = index + 3;
	indices[7] = index + 2;
	indices[8] = index + 0;
	indices[9] = index + 1;
	indices[10] = index + 4;
	indices[11] = index + 5;

	indices[12] = index + 1;
	indices[13] = index + 2;
	indices[14] = index + 5;
	indices[15] = index + 6;
	indices[16] = index + 4;
	indices[17] = index + 7;
}

void Cube::draw() {
	glDrawElements(GL_TRIANGLE_STRIP, 18, GL_UNSIGNED_INT, indices);
}

Cube::~Cube() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
