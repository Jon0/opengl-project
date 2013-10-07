/*
 * main.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <memory>

#include "scene/GRender.h"
#include "window/MainWindow.h"

using namespace std;

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);

	/** main window for render output */
	shared_ptr<MainWindow> mWnd( new MainWindow(800, 600, "Scene") );
	mWnd->start();

	shared_ptr<GRender> r{ new GRender() };
	r->start();

	/** camara to view scene */
	shared_ptr<Camera> camera = shared_ptr<Camera>( new Camera( r, mWnd ) );
	mWnd->addView( camera );
	shared_ptr<Ortho> ortho = shared_ptr<Ortho>( new Ortho( r, mWnd ) );
	mWnd->addView( ortho );

	// start running
	glutMainLoop();
	return EXIT_SUCCESS;
}


