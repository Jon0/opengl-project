/*
 * DrawList.cpp
 *
 *  Created on: 19/09/2013
 *      Author: remnanjona
 */

#include <iostream>
#include "DrawList.h"

namespace std {

DrawList::DrawList(vector<GPolygon> shape) {
	data = shape;
	s = shape.size();
	elementbuffer = 0;

	transform = glm::mat4(1.0f);
}

DrawList::~DrawList() {}

void DrawList::init(VertexBuffer *vb) {
	/* the order verticies get drawn */
	std::vector<unsigned int> indices;
	int off = vb->size();

	vector<GVertex> verts;
	for (GPolygon poly: data) {
		for (GVertex vert: poly) {
			verts.push_back(vert);
			indices.push_back(off);
			off++;
		}
	}
	vb->add(verts);

	// Generate a buffer for the indices
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

void DrawList::draw() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glDrawElements(GL_TRIANGLES, s * 3, GL_UNSIGNED_INT, 0);
}

void DrawList::drawDebug() {
	vector<GVertex> verts;
	for (GPolygon poly: data) {
		for (GVertex vert: poly) {
			glBegin(GL_LINES);
			glColor3f(1,1,1);
			glVertex3fv(vert.e[POS].v);
			glVertex3fv((vert.e[POS] + vert.e[NORM]*0.1).v);
			glColor3f(1,0,0);
			glVertex3fv(vert.e[POS].v);
			glVertex3fv((vert.e[POS] + vert.basis.v[0]*0.1).v);
			glColor3f(0,1,0);
			glVertex3fv(vert.e[POS].v);
			glVertex3fv((vert.e[POS] + vert.basis.v[1]*0.1).v);
			glColor3f(0,0,1);
			glVertex3fv(vert.e[POS].v);
			glVertex3fv((vert.e[POS] + vert.basis.v[2]*0.1).v);
			glEnd();
		}
	}
}

int DrawList::selectMouse(int, int) {
	return false;
}

} /* namespace std */
