/*
 * MouseListener.h
 *
 *  Created on: 26/08/2013
 *      Author: remnanjona
 */

#ifndef MOUSELISTENER_H_
#define MOUSELISTENER_H_

namespace std {

class MouseListener {
public:
	virtual int mouseClicked(GLuint, int, int, int, int) = 0;
	virtual int mouseDragged(GLuint, int x, int y) = 0;
	virtual ~MouseListener() {};
};

} /* namespace std */
#endif /* MOUSELISTENER_H_ */
