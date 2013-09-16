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

void drawString(string message);

class Ortho: public ViewInterface {
public:
	Ortho( SceneInterface *, shared_ptr<MainWindow> );
	virtual ~Ortho();

	virtual void setView( chrono::duration<double> );
	virtual void resize(int, int);
	virtual void keyPressed(unsigned char);
	virtual int mouseClicked(int, int, int, int);
	virtual int mouseDragged(int, int);
	virtual Quaternion cameraAngle();
	virtual Vec3D unProject(int, int);

protected:
	int view_width, view_height;
	shared_ptr<MainWindow> wnd;
	SceneInterface *scene;
	string message;
};

} /* namespace std */
#endif /* ORTHO_H_ */
