/*
 * SceneInterface.h
 *
 *  Created on: 14/09/2013
 *      Author: remnanjona
 */

#ifndef SCENEINTERFACE_H_
#define SCENEINTERFACE_H_

#include <string>
#include <chrono>

namespace std {

class ViewInterface;

class SceneInterface {
public:
	virtual ~SceneInterface() {};

	virtual void display( ViewInterface *, chrono::duration<double> ) = 0;
	virtual int mouseClicked( ViewInterface *, int, int, int, int ) = 0;
	virtual int mouseDragged( ViewInterface *, int, int ) = 0;
	virtual void messageSent(string) = 0;
	virtual void keyPressed(unsigned char) = 0;
};

} /* namespace std */
#endif /* SCENEINTERFACE_H_ */
