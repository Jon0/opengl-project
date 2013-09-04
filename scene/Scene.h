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
#include "../geometry/Animation.h"

namespace std {

class Scene: public Camera {
public:
	Scene();
	virtual ~Scene();

	virtual int clickInner(int, int);
	virtual int dragInner(int, int);
	void keyPressed(unsigned char);
	virtual void display();
protected:
	int selectedBone;
	int clickx, clicky;
	float roll;
	Quaternion *click_q;
	SkeletonLoader *loader;
	Skeleton *skeleton;
	Animation *animation;
};

} /* namespace std */
#endif /* SCENE_H_ */
