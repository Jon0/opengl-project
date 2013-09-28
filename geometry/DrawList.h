/*
 * DrawList.h
 *
 *  Created on: 19/09/2013
 *      Author: remnanjona
 */

#ifndef DRAWLIST_H_
#define DRAWLIST_H_

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "../texture/Tex.h"
#include "Geometry.h"
#include "GVertex.h"

namespace std {

class DrawList: public Geometry {
public:
	DrawList( vector<GPolygon> );
	virtual ~DrawList();

	virtual void init(VertexBuffer *);
	virtual void draw();
	virtual void drawDebug();

	virtual int selectMouse( int, int );

	/*
	 * do these need to be kept?
	 */
	unsigned int s;
	vector<GPolygon> data;

	/* Transformation */
	glm::mat4 transform;

	/* Indices */
	GLuint elementbuffer;
};

} /* namespace std */
#endif /* DRAWLIST_H_ */
