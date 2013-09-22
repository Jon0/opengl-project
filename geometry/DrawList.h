/*
 * DrawList.h
 *
 *  Created on: 19/09/2013
 *      Author: remnanjona
 */

#ifndef DRAWLIST_H_
#define DRAWLIST_H_

#include <GL/glut.h>
#include "Drawable.h"
#include "GVertex.h"

namespace std {

class DrawList: public Drawable {
public:
	DrawList(vector<GPolygon>, GLenum drawMode);
	virtual ~DrawList();

	virtual void display();
	virtual int selectMouse(int, int);

	void setBumpMap(const char *filename);

	int m_glGeomListPoly;
};

} /* namespace std */
#endif /* DRAWLIST_H_ */
