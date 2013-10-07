/*
 * Positional.h
 *
 *  Created on: 8/10/2013
 *      Author: remnanjona
 */

#ifndef POSITIONAL_H_
#define POSITIONAL_H_

#include "../Light.h"

namespace std {

class Positional: public Light {
public:
	Positional();
	virtual ~Positional();
	virtual glm::mat4 getTransform();
};

} /* namespace std */
#endif /* POSITIONAL_H_ */
