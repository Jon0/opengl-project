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

class ViewInterface: public KeyListener, public MouseListener {
public:
	virtual void setView(GLuint, chrono::duration<double>) = 0;
	virtual void resize(GLuint, int, int) = 0;
	virtual void keyPressed(GLuint, unsigned char) = 0;
	virtual int mouseClicked(GLuint, int, int, int, int) = 0;
	virtual int mouseDragged(GLuint, int, int) = 0;
	virtual ~ViewInterface() {};
};

} /* namespace std */
#endif /* VIEWINTERFACE_H_ */
