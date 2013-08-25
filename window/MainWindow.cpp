/*
 * MainWindow.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <GL/glut.h>
#include "MainWindow.h"

namespace std {

/* pointer to the running instance */
MainWindow *ins;

MainWindow::MainWindow() {
	ins = this;
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	g_mainWnd = glutCreateWindow("COMP308 Assignment2");
	glutDisplayFunc(displayCallback);

	// start running
	glutMainLoop();
}

void MainWindow::display() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	for (auto view: g_view) {
		ViewInterface *i = view;
		i->display();
	}
	glutSwapBuffers();
}

void MainWindow::displayCallback() {
	ins->display();
}

MainWindow::~MainWindow() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
