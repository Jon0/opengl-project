/*
 * Spotlight.h
 *
 *  Created on: 8/10/2013
 *      Author: remnanjona
 */

#ifndef SPOTLIGHT_H_
#define SPOTLIGHT_H_

#include "../Light.h"

namespace std {

class Spotlight: public Light {
public:
	Spotlight();
	virtual ~Spotlight();
	virtual glm::mat4 getTransform();
};

} /* namespace std */
#endif /* SPOTLIGHT_H_ */
