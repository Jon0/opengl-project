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

class Scene: public SceneInterface {
public:
	Scene();
	virtual ~Scene();

	void getBoneAlignment(Quaternion, Quaternion, Quaternion *);
	void keyPressed(unsigned char);

	virtual void display( ViewInterface *, chrono::duration<double> );
	virtual int mouseClicked( ViewInterface *, int, int, int, int );
	virtual int mouseDragged( ViewInterface *, int, int );
protected:
	Quaternion click_old, click_new;
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
