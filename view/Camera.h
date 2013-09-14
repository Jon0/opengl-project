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
#include "../scene/SceneInterface.h"
#include "../window/MainWindow.h"
#include "../window/MouseListener.h"

namespace std {

Quaternion *getArc(int arcx, int arcy, int ix, int iy, float rad, Quaternion *result);

class Camera: public ViewInterface {
public:
	Camera( SceneInterface *, MainWindow * );
	virtual ~Camera();

	virtual void setView( chrono::duration<double> );
	virtual void resize(int, int);
	virtual void keyPressed(unsigned char);
	virtual int mouseClicked(int, int, int, int);
	virtual int mouseDragged(int, int);
	virtual Quaternion cameraAngle();

	void setupMatrix();
	GLfloat *getProjMatrix();
	GLfloat *getModelMatrix();
	void turn(Quaternion *);

private:
	MainWindow *wnd;
	SceneInterface *scene;
	Vec3D focus;
	Quaternion cam_angle, cam_angle_d, click_old, click_new;
	bool button_state[5];
	float viewzoom, cam_aspect, arcball_radius, arcball_x, arcball_y;
	GLfloat temp_matrix [16];
	GLfloat proj_matrix [16];
	GLfloat model_matrix [16];
};

} /* namespace std */
#endif /* CAMERA_H_ */
