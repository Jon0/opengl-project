/*
 * Cube.h
 *
 *  Created on: 11/05/2013
 *      Author: remnanjona
 */

#ifndef CUBE_H_
#define CUBE_H_

#include "Geometry.h"
#include "../buffer/VertexBuffer.h"

namespace std {

class Cube:
		public Geometry
{
	float size;
	long index;
	GLuint *indices;
public:
	Cube(float);
	void init(VertexBuffer *);
	virtual void draw();
	virtual ~Cube();
};

} /* namespace std */
#endif /* CUBE_H_ */
