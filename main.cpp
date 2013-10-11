/*
 * main.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <memory>

#include "../pipeline/Pipeline.h"
#include "scene/GRender.h"
#include "window/MainWindow.h"

using namespace std;

/* the scene to render */
shared_ptr<GRender> scene;

/** camara to draw scene onto the window */
shared_ptr<Camera> camera;
shared_ptr<Ortho> ortho;


/* a pipeline to render with */
shared_ptr<Pipeline> pipeline;

void updateFunc( chrono::duration<double> tick ) {
	scene->update( tick );

	pipeline->run( scene );
}

int main(int argc, char *argv[]) {
	srand( time( NULL ) );
	glutInit(&argc, argv);

	/** setup main window for render output */
	shared_ptr<MainWindow> mWnd( new MainWindow(800, 600, "Scene") );

	/* prepare scene */
	pipeline = shared_ptr<Pipeline>{};
	scene = shared_ptr<GRender>{ new GRender() };
	camera = shared_ptr<Camera>{ new Camera( scene ) };
	ortho = shared_ptr<Ortho>{ new Ortho( scene ) };

	mWnd->start();
	mWnd->addView( camera );
	mWnd->addView( ortho );
	mWnd->setUpdateFunc(updateFunc);

	/* start running */
	glutMainLoop();
	return EXIT_SUCCESS;
}



