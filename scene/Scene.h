/*
 * Scene.h
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <memory>
#include "SpeedCurve.h"
#include "play/SkeletonTransform.h"
#include "../view/Camera.h"
#include "../load/SkeletonLoader.h"
#include "../geometry/Skeleton.h"

namespace std {

class Scene: public SceneInterface {
public:
	Scene(string);
	Scene(const Scene &);
	virtual ~Scene();

	void getBoneAlignment(Quaternion, Quaternion, Quaternion *);
	int mouseSelect(int, int);


	virtual void display( ViewInterface *, chrono::duration<double> );
	virtual int mouseClicked( ViewInterface *, int, int, int, int );
	virtual int mouseDragged( ViewInterface *, int, int );
	virtual void messageSent(string);
	virtual void keyPressed(unsigned char);
protected:
	shared_ptr<Camera> camera;
	shared_ptr<SkeletonLoader> loader;
	shared_ptr<Skeleton> skeleton;

	SkeletonTransform player;
	Quaternion click_old, click_new;

	bool playing, drag_bone;
	chrono::duration<double> time;

	int selectedBone, clickx, clicky;
};

} /* namespace std */
#endif /* SCENE_H_ */
