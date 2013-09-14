/*
 * ViewInterface.h
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#ifndef VIEWINTERFACE_H_
#define VIEWINTERFACE_H_

#include <chrono>
#include "../window/KeyListener.h"
#include "../window/MouseListener.h"

namespace std {

class Quaternion;

class ViewInterface: public KeyListener, public MouseListener {
public:
	virtual ~ViewInterface() {};

	virtual void setView( chrono::duration<double> ) = 0;
	virtual void resize(int, int) = 0;
	virtual void keyPressed(unsigned char) = 0;
	virtual int mouseClicked(int, int, int, int) = 0;
	virtual int mouseDragged(int, int) = 0;
	virtual Quaternion cameraAngle() = 0;
};

} /* namespace std */
#endif /* VIEWINTERFACE_H_ */
