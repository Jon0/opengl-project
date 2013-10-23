/*
 * main.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <memory>


#include "pipeline/Pipeline.h"
#include "view/Camera.h"
#include "window/MainWindow.h"

using namespace std;

/* a pipeline to render with */
shared_ptr<Pipeline> pipeline;

/** camara to draw scene onto the window */
shared_ptr<Camera> camera;

int main(int argc, char *argv[]) {
	srand( time( NULL ) );
	glutInit(&argc, argv);

	/**
	 * setup main window for render output
	 * - must go first
	 */
	shared_ptr<MainWindow> mWnd( new MainWindow(800, 600, "Scene") );

	/* pipeline setup */
	pipeline = shared_ptr<Pipeline>{ new Pipeline() };

	/* prepare scene */
	camera = shared_ptr<Camera>{ new Camera( pipeline ) };

	mWnd->start();
	mWnd->addView( camera );
	mWnd->setUpdateFunc( pipeline );

	/* start running */
	glutMainLoop();
	return EXIT_SUCCESS;
}



