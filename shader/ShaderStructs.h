/*
 * ShaderStructs.h
 *
 *  Created on: 1/10/2013
 *      Author: remnanjona
 */

#ifndef SHADERSTRUCTS_H_
#define SHADERSTRUCTS_H_

#include <GL/gl.h>
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

struct OctreeNode {
	// pointers to gpu memory
	GLuint64 parent;
	GLuint64 children [8];

	// node attributes
	glm::vec4 normal;
	glm::vec4 color;
	glm::vec4 emission;
};

struct BoneProperties {
	glm::vec4 position;
};

} /* namespace std */
#endif /* SHADERSTRUCTS_H_ */
