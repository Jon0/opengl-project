/*
 * DrawList.cpp
 *
 *  Created on: 19/09/2013
 *      Author: remnanjona
 */

#include "DrawList.h"

namespace std {

DrawList::DrawList(vector<GPolygon> shape, GLenum drawMode) {

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
