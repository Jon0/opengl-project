/*
 * Scene.h
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "../view/Camera.h"
#include "../load/SkeletonLoader.h"
#include "../geometry/Skeleton.h"

namespace std {

class Scene: public Camera {
public:
	Scene();
	virtual ~Scene();

	virtual int clickInner(int, int);
	virtual int dragInner(int, int);
	virtual void display();
protected:
	int clickx, clicky;
	SkeletonLoader *loader;
	Skeleton *skeleton;
};

} /* namespace std */
#endif /* SCENE_H_ */
