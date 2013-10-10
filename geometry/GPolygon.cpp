/*
 * GPolygon.cpp
 *
 *  Created on: 10/10/2013
 *      Author: asdf
 */

#include "GPolygon.h"

namespace std {

GPolygon::GPolygon() {
	// TODO Auto-generated constructor stub

}

GPolygon::~GPolygon() {
	// TODO Auto-generated destructor stub
}

glm::vec3 GPolygon::center() {
	glm::vec3 total;
	for (GVertex v: *this) {
		total += v.position;
	}
	total /= size();
	return total;
}

glm::vec3 GPolygon::normal() {
	glm::vec3 total(0,0,0);
	for (GVertex v: *this) {
		total += v.normal;
	}
	if (glm::length(total) == 0) return total;
	return glm::normalize(total);
}

} /* namespace std */
