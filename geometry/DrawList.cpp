/*
 * DrawList.cpp
 *
 *  Created on: 19/09/2013
 *      Author: remnanjona
 */

#include "DrawList.h"

namespace std {

DrawList::DrawList(vector<GPolygon> shape, GLenum drawMode) {


	//float *t = new float(shape.size() * 3 * 3);
	//float *b = new float(shape.size() * 3 * 3);

	for (unsigned int i = 0; i < shape.size(); ++i) {
		for (unsigned int v = 0; v < shape[i].size(); ++v) {
			//t[i * 3 * 3 + v * 3 + 0] = shape.data()[i].data()[v].basis.v[0].v[0];
			//t[i * 3 * 3 + v * 3 + 1] = shape.data()[i].data()[v].basis.v[0].v[1];
			//t[i * 3 * 3 + v * 3 + 2] = shape.data()[i].data()[v].basis.v[0].v[2];
			//b[i * 3 * 3 + v * 3 + 0] = shape.data()[i].data()[v].basis.v[1].v[0];
			//b[i * 3 * 3 + v * 3 + 1] = shape.data()[i].data()[v].basis.v[1].v[1];
			//b[i * 3 * 3 + v * 3 + 2] = shape.data()[i].data()[v].basis.v[1].v[2];
		}
	}

	//GLuint tangentbuffer;
	//glGenBuffers(1, &tangentbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
	//glBufferData(GL_ARRAY_BUFFER, shape.size() * 3 * 3 * sizeof(float), &t, GL_STATIC_DRAW);

	//GLuint bitangentbuffer;
	//glGenBuffers(1, &bitangentbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
	//glBufferData(GL_ARRAY_BUFFER, shape.size() * 3 * 3 * sizeof(float), &b, GL_STATIC_DRAW);




	// Assign a display list; return 0 if err
	m_glGeomListPoly = glGenLists(1);
	glNewList(m_glGeomListPoly, GL_COMPILE);

	/*
	 * draw the shape
	 */
	glBegin(drawMode);
	for (unsigned int i = 0; i < shape.size(); ++i) {
		for (unsigned int v = 0; v < shape[i].size(); ++v) {
			float *uv = shape[i][v].getTexCoord().v;
			float *norm = shape[i][v].getNormal().v;
			float *pos = shape[i][v].getPosition().v;
			glTexCoord3fv(uv);
			glNormal3fv(norm);
			glVertex3fv(pos);
		}
	}
	glEnd();

	glEndList();

}

DrawList::~DrawList() {
	glDeleteLists(m_glGeomListPoly, 1);
}

void DrawList::display() {
	//glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	/* draw */
	glCallList(m_glGeomListPoly);
}

int DrawList::selectMouse(int, int) {
	return false;
}

} /* namespace std */
