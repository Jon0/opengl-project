/*
 * VertexBuffer.h
 *
 *  Created on: 30/04/2013
 *      Author: remnanjona
 */

#ifndef VERTEXBUFFER_H_
#define VERTEXBUFFER_H_

#include <vector>
#include <GL/glut.h>
#include "V3D.h"

namespace std {

class VertexBuffer {
	int stride;
	GLuint vb;
	vector<V3D> vert;
public:
	VertexBuffer(int);
	GLuint addr();
	long add( vector<V3D> & );
	void store();
	virtual ~VertexBuffer();
};

} /* namespace std */
#endif /* VERTEXBUFFER_H_ */
