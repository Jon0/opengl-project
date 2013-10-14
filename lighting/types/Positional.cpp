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

unsigned int Positional::mapSize() {
	return 1024 * 4;
}

unsigned int Positional::cull() {
	return GL_FRONT;
}

glm::mat4 Positional::getTransform() {
	glm::mat4 depthProjectionMatrix = glm::perspective<float>(90.0, 1.0, 10.0, 5000.0);
	glm::mat4 depthViewMatrix = glm::lookAt(glm::vec3(data.position * 2), glm::vec3(0,0,0), glm::vec3(0,1,0));
	return depthProjectionMatrix * depthViewMatrix;
}

} /* namespace std */
