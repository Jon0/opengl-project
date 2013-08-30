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
#include "../math/Quaternion.h"
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
	Quaternion *click;
	Quaternion *cam_angle;
	Vec3D *focus;
	float viewzoom, cam_aspect;
	SceneInterface *scene;
	void setCamera();
	Quaternion *getArc(int x, int y);
};

} /* namespace std */
#endif /* CAMERA_H_ */
