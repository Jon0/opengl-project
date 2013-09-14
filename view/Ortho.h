/*
 * Ortho.h
 *
 *  Created on: 26/08/2013
 *      Author: remnanjona
 */

#ifndef ORTHO_H_
#define ORTHO_H_

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
	Ortho( SceneInterface *, MainWindow * );
	virtual ~Ortho();

	virtual void setView( chrono::duration<double> );
	virtual void resize(int, int);
	virtual void keyPressed(unsigned char);
	virtual int mouseClicked(int, int, int, int);
	virtual int mouseDragged(int, int);
	virtual Quaternion cameraAngle();

protected:
	MainWindow *wnd;
	SceneInterface *scene;
	int view_width, view_height;

	string message; // TODO need a message?
};

} /* namespace std */
#endif /* ORTHO_H_ */
