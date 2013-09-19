/*
 * Render.cpp
 *
 *  Created on: 19/09/2013
 *      Author: remnanjona
 */

#include "Render.h"

namespace std {

Render::Render():
	mWnd{new MainWindow(800, 600, "Scene")} {
	mWnd->start();

	g = new G308_Geometry();
	shape = g->readOBJ("assets/obj/Teapot.obj");
}

Render::~Render() {
	// TODO Auto-generated destructor stub
}

void Render::start() {
	camera = shared_ptr<Camera>{ new Camera( shared_from_this(), mWnd ) };
	mWnd->addView( camera );
}

void Render::display( shared_ptr<ViewInterface>, chrono::duration<double> ) {

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < shape.size(); ++i) {
		for (int v = 0; v < shape[i].size(); ++v) {
			glNormal3fv((float *)&shape[i][v].n);
			glVertex3fv((float *)&shape[i][v].p);
		}
	}
	glEnd();
}

int Render::mouseClicked( shared_ptr<ViewInterface>, int, int, int, int ) {
	return false;
}

int Render::mouseDragged( shared_ptr<ViewInterface>, int, int ) {
	return false;
}

void Render::messageSent(string) {

}

void Render::keyPressed(unsigned char) {

}

} /* namespace std */
