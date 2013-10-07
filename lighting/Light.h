/*
 * Light.h
 *
 *  Created on: 8/10/2013
 *      Author: remnanjona
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include <glm/glm.hpp>

#include "../shader/ShaderStructs.h"
#include "../shader/UBO.h"

namespace std {

class Light: public UBO<LightProperties> {
public:
	virtual ~Light() {}
	virtual glm::mat4 getTransform() = 0;
};

} /* namespace std */
#endif /* LIGHT_H_ */
