/*
 * GMesh.h
 *
 *  Created on: 15/10/2013
 *      Author: remnanjona
 */

#ifndef GMESH_H_
#define GMESH_H_

#include "../texture/Tex.h"
#include "GPolygon.h"

namespace std {

class GMesh: public vector<GPolygon> {
public:
	Tex *texture;
	GLuint texaddr;

	GMesh();
	virtual ~GMesh();
};

} /* namespace std */
#endif /* GMESH_H_ */
