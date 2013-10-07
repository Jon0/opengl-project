/*
 * SceneInterface.h
 *
 *  Created on: 14/09/2013
 *      Author: remnanjona
 */

#ifndef SCENEINTERFACE_H_
#define SCENEINTERFACE_H_

#include <memory>
#include <string>
#include <chrono>

namespace std {

class ViewInterface;

class SceneInterface {
public:
	virtual ~SceneInterface() {};

	// TODO prepare should get time tick
	virtual void prepare() = 0;
	virtual void display( shared_ptr<ViewInterface>, chrono::duration<double> ) = 0;
	virtual void displayUI() = 0;
	virtual int mouseClicked( shared_ptr<ViewInterface>, int, int, int, int ) = 0;
	virtual int mouseDragged( shared_ptr<ViewInterface>, int, int ) = 0;
	virtual void messageSent(string) = 0;
	virtual void keyPressed(unsigned char) = 0;
};

} /* namespace std */
#endif /* SCENEINTERFACE_H_ */
