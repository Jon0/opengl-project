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

#include "../input/MouseListener.h"
#include "../math/Vec3D.h"
#include "../math/Quaternion.h"
#include "../scene/SceneInterface.h"
#include "../shader/ShaderStructs.h"
#include "../shader/UBO.h"
#include "../shader/UniformControl.h"
#include "../window/MainWindow.h"
#include "ViewInterface.h"

namespace std {

class Pipeline;

void getArc(int, int, int, int, float, glm::quat &);
void getUnitCircle(int, int, int, int, glm::quat &);

class Camera: public ViewInterface {
private:
	//shared_ptr<MainWindow> wnd;
	shared_ptr<Pipeline> pipeline;
	glm::vec3 focus;
	glm::quat cam_angle, cam_angle_d, click_old, click_new;
	bool control[3];
	int windowwidth, windowheight, click_x, click_y;
	float viewzoom, cam_aspect, arcball_radius, arcball_x, arcball_y;
	GLfloat temp_matrix [16], proj_matrix [16], model_matrix [16];
	GLdouble proj_matrixd [16], model_matrixd [16];
	UBO<CameraProperties> camera_properties;

public:
	Camera( shared_ptr<Pipeline> );
	virtual ~Camera();

	virtual void setView( chrono::duration<double> );
	virtual void resize(int, int);
	virtual void keyPressed(unsigned char);
	virtual int mouseClicked(int, int, int, int);
	virtual int mouseDragged(int, int);
	virtual glm::quat cameraAngle();
	virtual glm::vec3 project(const glm::vec3 &);
	virtual glm::vec3 unProject(int, int);
	virtual glm::mat4 viewMatrix();
	virtual glm::mat4 projectionMatrix();
	virtual UBO<CameraProperties> *properties();

	/* TODO remove */
	void setupMatrix();
};

} /* namespace std */
#endif /* CAMERA_H_ */
