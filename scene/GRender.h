/*
 * GRender.h
 *
 *  Created on: 23/09/2013
 *      Author: remnanjona
 */

#ifndef GRENDER_H_
#define GRENDER_H_

#include <memory>
#include "SceneInterface.h"
#include "../geometry/Geometry.h"
#include "../lighting/Lighting.h"
#include "../load/GeometryLoader.h"
#include "../shader/Program.h"
#include "../texture/Tex.h"
#include "../view/Camera.h"
#include "../window/MainWindow.h"

namespace std {

class GRender:
		public enable_shared_from_this<GRender>,
		public SceneInterface {
public:
	shared_ptr<MainWindow> mWnd;
	Program program;
	GeometryLoader gloader;
	shared_ptr<Camera> camera;
	shared_ptr<Lighting> light;
	shared_ptr<Geometry> obj;

	GRender();
	virtual ~GRender();

	void start();

	virtual void prepare();
	virtual void display( shared_ptr<ViewInterface>, chrono::duration<double> );
	virtual int mouseClicked( shared_ptr<ViewInterface>, int, int, int, int );
	virtual int mouseDragged( shared_ptr<ViewInterface>, int, int );
	virtual void messageSent(string);
	virtual void keyPressed(unsigned char);
};

} /* namespace std */
#endif /* GRENDER_H_ */
