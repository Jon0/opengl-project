/*
 * Directional.h
 *
 *  Created on: 8/10/2013
 *      Author: remnanjona
 */

#ifndef DIRECTIONAL_H_
#define DIRECTIONAL_H_

#include "../Light.h"

namespace std {

class Directional: public Light {
public:
	Directional();
	virtual ~Directional();
	virtual glm::mat4 getTransform();
};

} /* namespace std */
#endif /* DIRECTIONAL_H_ */
