/*
 * GPolygon.h
 *
 *  Created on: 10/10/2013
 *      Author: asdf
 */

#ifndef GPOLYGON_H_
#define GPOLYGON_H_

#include <vector>
#include <glm/glm.hpp>

#include "GVertex.h"

namespace std {

class GPolygon: public vector<GVertex> {
public:
	GPolygon();
	virtual ~GPolygon();

	glm::vec3 center();
	glm::vec3 normal();
};

} /* namespace std */
#endif /* GPOLYGON_H_ */
