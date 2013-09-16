/*
 * Camera.h
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <memory>
#include <GL/glut.h>
#include "ViewInterface.h"
#include "../math/Vec3D.h"
#include "../math/Quaternion.h"
#include "../scene/SceneInterface.h"
#include "../window/MainWindow.h"
#include "../window/MouseListener.h"

namespace std {

void getArc(int, int, int, int, float, Quaternion *);
void getUnitCircle(int, int, int, int, Quaternion *);

class Camera: public ViewInterface {
public:
	Camera( SceneInterface *, shared_ptr<MainWindow> );
	virtual ~Camera();

	virtual void setView( chrono::duration<double> );
	virtual void resize(int, int);
	virtual void keyPressed(unsigned char);
	virtual int mouseClicked(int, int, int, int);
	virtual int mouseDragged(int, int);
	virtual Quaternion cameraAngle();
	virtual Vec3D unProject(int, int);

	void setupMatrix();
	GLfloat *getProjMatrix();
	GLfloat *getModelMatrix();

private:
	shared_ptr<MainWindow> wnd;
	SceneInterface *scene;
	Vec3D focus;
	Quaternion cam_angle, cam_angle_d, click_old, click_new;
	bool control[3];
	int click_x, click_y;
	float viewzoom, cam_aspect, arcball_radius, arcball_x, arcball_y;
	GLfloat temp_matrix [16], proj_matrix [16], model_matrix [16];
	GLdouble proj_matrixd [16], model_matrixd [16];
};

} /* namespace std */
#endif /* CAMERA_H_ */
