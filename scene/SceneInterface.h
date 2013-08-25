/*
 * SceneInterface.h
 *
 *  Created on: 26/08/2013
 *      Author: remnanjona
 */

#ifndef SCENEINTERFACE_H_
#define SCENEINTERFACE_H_

namespace std {

class SceneInterface {
public:
	virtual void display() = 0;
	virtual ~SceneInterface() {};
};

} /* namespace std */
#endif /* SCENEINTERFACE_H_ */
