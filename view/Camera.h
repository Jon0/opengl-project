/*
 * Camera.h
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "ViewInterface.h"
#include "../math/Vec3D.h"
#include "../window/MouseListener.h"
#include "../scene/SceneInterface.h"

namespace std {

class Camera: public ViewInterface, public MouseListener {
public:
	Camera(SceneInterface *, float);
	virtual ~Camera();
	virtual void display();
	virtual void mouseClicked(int, int, int, int);
	void turn(int, int);
protected:
	int mouse_x, mouse_y;
	float viewzoom, angletilt, angleflat, cam_aspect;
	Vec3D *focus;
	SceneInterface *scene;
	void setCamera();
};

} /* namespace std */
#endif /* CAMERA_H_ */
