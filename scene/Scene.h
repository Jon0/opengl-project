/*
 * Scene.h
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "../view/Camera.h"
#include "../load/AnimationLoader.h"
#include "../load/SkeletonLoader.h"
#include "../geometry/Skeleton.h"
#include "../spline/Animation.h"
#include "../spline/Path.h"

namespace std {

class Scene: public Camera {
public:
	Scene();
	virtual ~Scene();

	void getBoneAlignment(Quaternion, Quaternion *);
	virtual int clickInner(int, int);
	virtual int dragInner(int, int);
	void keyPressed(unsigned char);
	virtual void display(chrono::duration<double>);
protected:
	chrono::duration<double> time;
	int selectedBone, clickx, clicky;
	SkeletonLoader *loader;
	AnimationLoader *aloader;
	Skeleton *skeleton;
	Animation *animation;
	Path *path;
	pose p;
	bool playing;
};

} /* namespace std */
#endif /* SCENE_H_ */
