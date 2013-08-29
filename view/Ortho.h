/*
 * Ortho.h
 *
 *  Created on: 26/08/2013
 *      Author: remnanjona
 */

#ifndef ORTHO_H_
#define ORTHO_H_

#include <string>
#include "ViewInterface.h"
#include "../geometry/Spline.h"
#include "../window/KeyListener.h"
#include "../window/MouseListener.h"

namespace std {

class Ortho: public ViewInterface, public KeyListener, public MouseListener {
public:
	Ortho();
	void setView();
	virtual void display();
	virtual void keyPressed(unsigned char);
	virtual void mouseClicked(int, int);
	virtual ~Ortho();
protected:
	Spline *spline;
	string message;
};

} /* namespace std */
#endif /* ORTHO_H_ */
