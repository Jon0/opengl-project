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
#include "../view/Ortho.h"
#include "../load/SkeletonLoader.h"
#include "../geometry/Skeleton.h"
#include "../window/MainWindow.h"

namespace std {

class Scene:
		public enable_shared_from_this<Scene>,
		public SceneInterface {
public:
	Scene(string);
	Scene(const Scene &);
	virtual ~Scene();

	void getBoneAlignment(glm::quat, glm::quat, glm::quat &);
	int mouseSelect(int, int);

	virtual void prepare();
	virtual void display( shared_ptr<ViewInterface>, chrono::duration<double> );
	virtual int mouseClicked( shared_ptr<ViewInterface>, int, int, int, int );
	virtual int mouseDragged( shared_ptr<ViewInterface>, int, int );
	virtual void messageSent(string);
	virtual void keyPressed(unsigned char);

protected:
	shared_ptr<MainWindow> mWnd;
	shared_ptr<Camera> camera;
	shared_ptr<Ortho> ortho;
	shared_ptr<SkeletonLoader> loader;
	shared_ptr<Skeleton> skeleton;

	SkeletonTransform player;
	glm::quat click_old, click_new;

	bool playing, drag_bone;
	float time;
	int selectedBone, clickx, clicky;
};

} /* namespace std */
#endif /* SCENE_H_ */
