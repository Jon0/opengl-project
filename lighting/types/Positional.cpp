/*
 * Positional.cpp
 *
 *  Created on: 8/10/2013
 *      Author: remnanjona
 */

#include <glm/gtc/matrix_transform.hpp>

#include "Positional.h"

namespace std {

Positional::Positional() {

	// positional light
	data.position = glm::vec4(7.5, 2.0, 7.5, 1.0);
	data.color = glm::vec4(0.9, 0.9, 0.9, 1.0);
	data.intensity = 80.0;
	data.spotlight = 0.0;
	update();
}

Positional::~Positional() {
	// TODO Auto-generated destructor stub
}

glm::mat4 Positional::getTransform() {
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-20, 20, -20, 20, 0, 800);
	glm::vec3 p = glm::vec3(data.position);
	glm::mat4 depthViewMatrix = glm::lookAt(p, glm::vec3(0,0,0), glm::vec3(0,1,0));

	return depthProjectionMatrix * depthViewMatrix;
}

} /* namespace std */
