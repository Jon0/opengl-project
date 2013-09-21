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
#include "../geometry/GVertex.h"

namespace std {

class VertexBuffer {
	int stride;
	GLuint vb;
	vector<GVertex> vert;
public:
	VertexBuffer(int);
	GLuint addr();
	long add( vector<GVertex> & );
	void store();
	virtual ~VertexBuffer();
};

} /* namespace std */
#endif /* VERTEXBUFFER_H_ */
