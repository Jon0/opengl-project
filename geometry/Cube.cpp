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
}

Cube::~Cube() {
	// TODO Auto-generated destructor stub
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

	GLuint *indices = new GLuint[18];
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

	// Generate a buffer for the indices
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 18 * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

void Cube::draw() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glDrawElements(GL_TRIANGLE_STRIP, 18, GL_UNSIGNED_INT, 0);
}

void Cube::drawDebug() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glDrawElements(GL_TRIANGLE_STRIP, 18, GL_UNSIGNED_INT, 0);
}

glm::mat4 Cube::transform() {
	return glm::mat4(1.0);
}

void Cube::setTransform(glm::mat4) {

}

UBO<MaterialProperties> *Cube::materialUBO() {

}

MaterialProperties &Cube::material() {

}

void Cube::updateMaterial() {

}

} /* namespace std */
