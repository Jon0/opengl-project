/*
 * Camera.h
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <GL/glut.h>
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
	virtual void keyPressed(unsigned char) = 0;
	virtual int mouseClicked(int, int, int, int);
	virtual int mouseDragged(int x, int y);
	void setupMatrix();
	GLfloat *getProjMatrix();
	GLfloat *getModelMatrix();
	void turn(Quaternion *);
protected:
	Vec3D *focus;
	bool button_state[5];
	Quaternion *getArc(int x, int y);
	virtual int clickInner(int, int) = 0;
	virtual int dragInner(int, int) = 0;
	virtual void display() = 0;
private:
	Quaternion *click;
	Quaternion *cam_angle;
	float viewzoom, cam_aspect, arcball_radius, arcball_x, arcball_y;
	GLfloat temp_matrix [16];
	GLfloat proj_matrix [16];
	GLfloat model_matrix [16];
	void setClick(Quaternion *q);

};

} /* namespace std */
#endif /* CAMERA_H_ */
