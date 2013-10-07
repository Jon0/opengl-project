/*
 * Spotlight.cpp
 *
 *  Created on: 8/10/2013
 *      Author: remnanjona
 */

#include <glm/gtc/matrix_transform.hpp>

#include "Spotlight.h"

namespace std {

Spotlight::Spotlight() {

	data.position = glm::vec4(-74.9906, 53.8912, -13.388, 1.0);
	data.color = glm::vec4(0.3, 0.5, 0.9, 1.0);
	data.direction = glm::vec4(14.5201, 26.7082, 1.26496, 1.0);
	data.intensity = 20000.0;
	data.spotlight = cos(0.45);
	data.spotlightInner = cos(0.35);
	update();

}

Spotlight::~Spotlight() {
	// TODO Auto-generated destructor stub
}

glm::mat4 Spotlight::getTransform() {
	glm::mat4 depthProjectionMatrix = glm::perspective<float>(45.0, 1.0, 10.0, 5000.0);
	glm::mat4 depthViewMatrix = glm::lookAt(glm::vec3(data.position), glm::vec3(data.direction), glm::vec3(0,1,0));

	return depthProjectionMatrix * depthViewMatrix;
}

} /* namespace std */
