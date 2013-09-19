/*
 * Render.h
 *
 *  Created on: 19/09/2013
 *      Author: remnanjona
 */

#ifndef RENDER_H_
#define RENDER_H_

#include <memory>
#include "SceneInterface.h"
#include "../load/G308Geometry.h"
#include "../view/Camera.h"
#include "../window/MainWindow.h"

namespace std {

class Render:
		public enable_shared_from_this<Render>,
		public SceneInterface {
public:
	Render();
	void start();
	virtual ~Render();

	virtual void display( shared_ptr<ViewInterface>, chrono::duration<double> );
	virtual int mouseClicked( shared_ptr<ViewInterface>, int, int, int, int );
	virtual int mouseDragged( shared_ptr<ViewInterface>, int, int );
	virtual void messageSent(string);
	virtual void keyPressed(unsigned char);

	shared_ptr<MainWindow> mWnd;
	shared_ptr<Camera> camera;

	G308_Geometry *g;

	vector<GLpolygon> shape;
};

} /* namespace std */
#endif /* RENDER_H_ */
