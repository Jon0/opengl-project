/*
 * Geometry.h
 *
 *  Created on: 12/09/2013
 *      Author: remnanjona
 */

#include "../buffer/VertexBuffer.h"

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

namespace std {

class Geometry {
public:
	virtual ~Geometry() {}
	virtual void init(VertexBuffer *) = 0;
	virtual void draw() = 0;
	virtual void drawDebug() = 0;
};

} /* namespace std */
#endif /* GEOMETRY_H_ */
