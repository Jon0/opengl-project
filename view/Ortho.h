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
#include "../spline/Spline.h"
#include "../window/KeyListener.h"
#include "../window/MouseListener.h"

namespace std {

class Ortho: public ViewInterface {
public:
	Ortho();
	virtual void setView(chrono::duration<double>);
	virtual void resize(int, int);
	virtual void keyPressed(unsigned char);
	virtual int mouseClicked(int, int, int, int) = 0;
	virtual int mouseDragged(int x, int y) = 0;
	virtual ~Ortho();
protected:
	int view_width, view_height;
	string message;
	virtual void display(chrono::duration<double>) = 0;
	virtual void messageSent(string) = 0;
};

} /* namespace std */
#endif /* ORTHO_H_ */
