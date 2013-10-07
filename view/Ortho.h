/*
 * Ortho.h
 *
 *  Created on: 26/08/2013
 *      Author: remnanjona
 */

#ifndef ORTHO_H_
#define ORTHO_H_

#include <memory>
#include <string>
#include "ViewInterface.h"
#include "../spline/Spline.h"
#include "../window/KeyListener.h"
#include "../window/MouseListener.h"

namespace std {

class MainWindow;
class SceneInterface;

void drawString(string message, float x, float y);

class Ortho: public ViewInterface {
public:
	Ortho( shared_ptr<SceneInterface> );
	virtual ~Ortho();

	virtual void setView( chrono::duration<double> );
	virtual void resize(int, int);
	virtual void keyPressed(unsigned char);
	virtual int mouseClicked(int, int, int, int);
	virtual int mouseDragged(int, int);
	virtual glm::quat cameraAngle();
	virtual glm::vec3 project(const glm::vec3 &);
	virtual Vec3D unProject(int, int);
	virtual glm::mat4 viewMatrix();
	virtual glm::mat4 projectionMatrix();
	virtual UBO<CameraProperties> *properties();

protected:
	int view_width, view_height;
	shared_ptr<SceneInterface> scene;
	UBO<CameraProperties> ortho_properties;
	string message;
};

} /* namespace std */
#endif /* ORTHO_H_ */
