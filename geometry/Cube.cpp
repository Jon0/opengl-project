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
	elementbuffer = 0;
}

Cube::~Cube() {}

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

	// Order of vertex drawing
	GLuint *indices = new GLuint[18];
	int order[] = { 6, 2, 7, 3, 4, 0, 3, 2, 0, 1, 4, 5, 1, 2, 5, 6, 4, 7 };
	for (int i = 0; i < 18; ++i) indices[i] = index + order[i];

	// Generate a buffer for the indices
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 18 * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

void Cube::update( UniformBlock<BoneProperties> & ) {

}

void Cube::draw() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glDrawElements(GL_TRIANGLE_STRIP, 18, GL_UNSIGNED_INT, 0);
}

void Cube::drawDebug() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glDrawElements(GL_TRIANGLE_STRIP, 18, GL_UNSIGNED_INT, 0);
}

vector<GPolygon> &Cube::polygon(int) {
	return data;
}

glm::mat4 Cube::transform() {
	return glm::mat4(1.0);
}

void Cube::setTransform(glm::mat4) {

}

UBO<MaterialProperties> *Cube::materialUBO() {
	return &materialType;
}

MaterialProperties &Cube::material() {
	return materialType.data;
}

void Cube::updateMaterial() {
	return materialType.update();
}

} /* namespace std */
