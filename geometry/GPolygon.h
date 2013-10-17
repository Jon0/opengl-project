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

int triBoxOverlap(glm::vec3 boxcenter,glm::vec3 boxhalfsize, glm::vec3 triverts [3]);

class GPolygon: public vector<GVertex> {
public:
	GPolygon();
	virtual ~GPolygon();

	bool intersects(glm::vec3 centre, glm::vec3 size);
	glm::vec3 center();
	glm::vec3 normal();
};

} /* namespace std */
#endif /* GPOLYGON_H_ */
