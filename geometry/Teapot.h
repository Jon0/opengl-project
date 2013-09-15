/*
 * Teapot.h
 *
 *  Created on: 12/09/2013
 *      Author: remnanjona
 */

#ifndef TEAPOT_H_
#define TEAPOT_H_

#include "Drawable.h"

namespace std {

class Teapot: public Drawable {
public:
	Teapot();
	virtual ~Teapot();
	virtual void display();
	virtual int selectMouse(int, int);
};

} /* namespace std */
#endif /* TEAPOT_H_ */
