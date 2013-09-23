/*
 * GRender.cpp
 *
 *  Created on: 23/09/2013
 *      Author: remnanjona
 */

#include "../geometry/Cube.h"
#include "GRender.h"

namespace std {

GRender::GRender():
		program(),
		mWnd {new MainWindow(800, 600, "Scene")},
		obj { new Cube(20.0) }
{
	mWnd->start();
	program.setup( obj );
}

GRender::~GRender() {
	// TODO Auto-generated destructor stub
}

void GRender::start() {
	camera = shared_ptr<Camera>{ new Camera( shared_from_this(), mWnd ) };
	mWnd->addView( camera );
}

void GRender::prepare() {

}

void GRender::display( shared_ptr<ViewInterface>, chrono::duration<double> ) {
	program.enable();
	obj->draw();
}

int GRender::mouseClicked( shared_ptr<ViewInterface>, int, int, int, int ) {
	return false;
}

int GRender::mouseDragged( shared_ptr<ViewInterface>, int, int ) {
	return false;
}

void GRender::messageSent(string) {

}

void GRender::keyPressed(unsigned char) {

}

} /* namespace std */
