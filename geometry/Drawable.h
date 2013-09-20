/*
 * Drawable.h
 *
 *  Created on: 12/09/2013
 *      Author: remnanjona
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <vector>

namespace std {

struct GLpoint {
	float x;
	float y;
	float z;
};

typedef GLpoint GLnormal;

struct GLuvcoord {
	float u;
	float v;
};

struct GLvertex {
	GLpoint p;
	GLnormal n;
	GLuvcoord c;
};

typedef vector<GLvertex> GLpolygon;

class Drawable {
public:
	virtual ~Drawable() {}
	virtual void display() = 0;
	virtual int selectMouse(int, int) = 0;
};

} /* namespace std */
#endif /* DRAWABLE_H_ */
