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
#include <glm/glm.hpp>

#include "ViewInterface.h"
#include "../math/Vec3D.h"
#include "../math/Quaternion.h"
#include "../scene/SceneInterface.h"
#include "../shader/UBO.h"
#include "../shader/UniformControl.h"
#include "../window/MainWindow.h"
#include "../window/MouseListener.h"

namespace std {

struct CameraProperties {
	glm::mat4 P;
	glm::mat4 V;
	glm::mat4 M;
};

void getArc(int, int, int, int, float, Quaternion *);
void getUnitCircle(int, int, int, int, Quaternion *);

class Camera: public ViewInterface {
private:
	shared_ptr<MainWindow> wnd;
	shared_ptr<SceneInterface> scene;
	Vec3D focus;
	Quaternion cam_angle, cam_angle_d, click_old, click_new;
	bool control[3];
	int windowwidth, windowheight, click_x, click_y;
	float viewzoom, cam_aspect, arcball_radius, arcball_x, arcball_y;
	GLfloat temp_matrix [16], proj_matrix [16], model_matrix [16];
	GLdouble proj_matrixd [16], model_matrixd [16];

public:
	UBO<CameraProperties> properties;

	Camera( shared_ptr<SceneInterface>, shared_ptr<MainWindow> );
	virtual ~Camera();

	virtual void setView( chrono::duration<double> );
	virtual void resize(int, int);
	virtual void keyPressed(unsigned char);
	virtual int mouseClicked(int, int, int, int);
	virtual int mouseDragged(int, int);
	virtual Quaternion cameraAngle();
	virtual Vec3D unProject(int, int);
	virtual glm::mat4 viewMatrix();
	virtual glm::mat4 projectionMatrix();

	/* TODO remove */
	void setupMatrix();
};

} /* namespace std */
#endif /* CAMERA_H_ */
