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

namespace std {

class Camera: public ViewInterface {
public:
	Camera();
	virtual ~Camera();
	virtual void setView();
	virtual void resize(int, int);
	virtual void keyPressed(unsigned char);
	virtual int mouseClicked(int, int, int, int);
	void turn(int, int);

protected:
	Quaternion *click;
	Quaternion *cam_angle;
	Vec3D *focus;
	float viewzoom, cam_aspect;
	Quaternion *getArc(int x, int y);
	virtual void display() = 0;
};

} /* namespace std */
#endif /* CAMERA_H_ */
