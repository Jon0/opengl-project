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
#include "../scene/SceneInterface.h"

namespace std {

class Camera: public ViewInterface {
public:
	Camera(SceneInterface *, float);
	virtual void display();
	virtual ~Camera();
protected:
	float viewzoom, angletilt, angleflat, cam_aspect;
	Vec3D *focus;
	SceneInterface *scene;
	void setCamera();
};

} /* namespace std */
#endif /* CAMERA_H_ */
