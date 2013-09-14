/*
 * KeyListener.h
 *
 *  Created on: 26/08/2013
 *      Author: remnanjona
 */

#ifndef KEYLISTENER_H_
#define KEYLISTENER_H_

namespace std {

class KeyListener {
public:
	virtual void keyPressed(unsigned char) = 0;
	virtual ~KeyListener() {};
};

} /* namespace std */
#endif /* KEYLISTENER_H_ */
