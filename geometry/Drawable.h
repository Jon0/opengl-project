/*
 * Drawable.h
 *
 *  Created on: 12/09/2013
 *      Author: remnanjona
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <vector>
#include "../math/Basis.h"

namespace std {

class Drawable {
public:
	virtual ~Drawable() {}
	virtual void display() = 0;
	virtual int selectMouse(int, int) = 0;
};

} /* namespace std */
#endif /* DRAWABLE_H_ */
