/*
 * ShaderStructs.h
 *
 *  Created on: 1/10/2013
 *      Author: remnanjona
 */

#ifndef SHADERSTRUCTS_H_
#define SHADERSTRUCTS_H_

#include <glm/glm.hpp>

namespace std {

struct CameraProperties {
	glm::mat4 P;
	glm::mat4 V;
	glm::mat4 M;
};

struct LightProperties {
	glm::vec4 position;
	glm::vec4 color;
	glm::vec4 direction;
	float intensity;
	float spotlight;
	float spotlightInner;
};

struct MaterialProperties {
	glm::vec4 DiffuseColor;
	glm::vec4 AmbientColor;
	glm::vec4 SpecularColor;
	float Exponent;
};

} /* namespace std */
#endif /* SHADERSTRUCTS_H_ */
