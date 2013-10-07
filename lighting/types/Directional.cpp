/*
 * Directional.cpp
 *
 *  Created on: 8/10/2013
 *      Author: remnanjona
 */

#include <glm/gtc/matrix_transform.hpp>

#include "Directional.h"

namespace std {

Directional::Directional() {
	// directional light
	data.position = glm::vec4(-15.0, 10.0, -13.0, 0.0);
	data.color = glm::vec4(1.0, 0.85, 0.05, 1.0);
	data.intensity = 0.85;
	data.spotlight = 0.0;
	update();
}

Directional::~Directional() {
	// TODO Auto-generated destructor stub
}

glm::mat4 Directional::getTransform() {
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-400, 400, -400, 400, -1000, 1000);
	glm::vec3 p = glm::vec3(data.position);
	glm::mat4 depthViewMatrix = glm::lookAt(p, glm::vec3(0,0,0), glm::vec3(0,1,0));
	return depthProjectionMatrix * depthViewMatrix;
}

} /* namespace std */
