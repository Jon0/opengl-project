/*
 * Animation.h
 *
 *  Created on: 30/08/2013
 *      Author: remnanjona
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "Spline.h"

namespace std {

class Animation {
private:
	Spline *spline;
public:
	Animation(Spline *);
	virtual ~Animation();

	void display();
};

} /* namespace std */
#endif /* ANIMATION_H_ */
