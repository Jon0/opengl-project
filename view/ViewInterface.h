/*
 * ViewInterface.h
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#ifndef VIEWINTERFACE_H_
#define VIEWINTERFACE_H_

#include <memory>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "../shader/ShaderStructs.h"
#include "../shader/UBO.h"
#include "../window/KeyListener.h"
#include "../window/MouseListener.h"

namespace std {

class Vec3D; // TODO remove

class ViewInterface:
		public enable_shared_from_this<ViewInterface>,
		public KeyListener,
		public MouseListener {
public:
	virtual ~ViewInterface() {};

	virtual void setView( chrono::duration<double> ) = 0;
	virtual void resize(int, int) = 0;
	virtual void keyPressed(unsigned char) = 0;
	virtual int mouseClicked(int, int, int, int) = 0;
	virtual int mouseDragged(int, int) = 0;
	virtual glm::quat cameraAngle() = 0;
	virtual glm::vec3 project(const glm::vec3 &) = 0;
	virtual Vec3D unProject(int, int) = 0;
	virtual glm::mat4 viewMatrix() = 0;
	virtual glm::mat4 projectionMatrix() = 0;
	virtual UBO<CameraProperties> *properties() = 0;
};

} /* namespace std */
#endif /* VIEWINTERFACE_H_ */
