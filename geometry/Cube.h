/*
 * Cube.h
 *
 *  Created on: 11/05/2013
 *      Author: remnanjona
 */

#ifndef CUBE_H_
#define CUBE_H_

#include "../buffer/VertexBuffer.h"

namespace std {

class Cube {
	float size;
	long index;
	GLuint *indices;
public:
	Cube(float);
	void init(VertexBuffer *);
	void draw();
	virtual ~Cube();
};

} /* namespace std */
#endif /* CUBE_H_ */
