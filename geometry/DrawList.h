/*
 * DrawList.h
 *
 *  Created on: 19/09/2013
 *      Author: remnanjona
 */

#ifndef DRAWLIST_H_
#define DRAWLIST_H_

#include <GL/glut.h>

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
	virtual vector<GPolygon> &polygon();
	virtual glm::mat4 transform();
	virtual void setTransform(glm::mat4);
	virtual int selectMouse( int, int );
	virtual UBO<MaterialProperties> *materialUBO();
	virtual MaterialProperties &material();
	virtual void updateMaterial();

	/*
	 * do these need to be kept?
	 */
	unsigned int s;
	vector<GPolygon> data;

	/* Transformation */
	glm::mat4 transform_matrix;

	/* Indices */
	GLuint elementbuffer;

	/* material */
	UBO<MaterialProperties> materialType;
};

} /* namespace std */
#endif /* DRAWLIST_H_ */
