/*
 * DrawList.cpp
 *
 *  Created on: 19/09/2013
 *      Author: remnanjona
 */

#include "DrawList.h"

namespace std {

DrawList::DrawList(vector<GLpolygon> shape, GLenum drawMode) {

	// Assign a display list; return 0 if err
	m_glGeomListPoly = glGenLists(1);
	glNewList(m_glGeomListPoly, GL_COMPILE);

	/*
	 * draw the shape
	 */
	glBegin(drawMode);
	for (unsigned int i = 0; i < shape.size(); ++i) {
		for (unsigned int v = 0; v < shape[i].size(); ++v) {
			glNormal3fv((float *)&shape[i][v].n);
			glVertex3fv((float *)&shape[i][v].p);
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
