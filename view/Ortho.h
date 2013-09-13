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
	virtual ~Ortho();

	void drawString(string message);

	virtual void setView(GLuint, chrono::duration<double>);
	virtual void resize(GLuint, int, int);
	virtual void keyPressed(GLuint, unsigned char);
	virtual int mouseClicked(GLuint, int, int, int, int) = 0;
	virtual int mouseDragged(GLuint, int x, int y) = 0;

protected:
	int view_width, view_height;
	string message;
	virtual void display(GLuint view, chrono::duration<double>) = 0;
	virtual void messageSent(string) = 0;
};

} /* namespace std */
#endif /* ORTHO_H_ */
