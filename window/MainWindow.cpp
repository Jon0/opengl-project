/*
 * MainWindow.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <GL/glut.h>
#include "MainWindow.h"
#include "../view/Camera.h"
#include "../view/Ortho.h"
#include "../scene/Scene.h"

namespace std {

/* pointer to the running instance */
MainWindow *ins;

MainWindow::MainWindow(int width, int height) {
	ins = this;
	wnd_width = width;
	wnd_height = height;
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(wnd_width, wnd_height);
	g_mainWnd = glutCreateWindow("COMP308 Assignment 3");
	glutDisplayFunc(displayCallback);
	glutKeyboardFunc(keyboardCallback);
	glutMouseFunc(mouseCallback);
	glutMotionFunc(mouseCallbackMotionFunc);

	// add some views
	Camera *c = new Camera( new Scene(), (double) width / (double) height );
	mouse_focus = c;
	g_view.push_back( c );

	Ortho *o = new Ortho();
	key_focus = o;
	mouse_focus = o;
	g_view.push_back( o );

	// start running
	glutMainLoop();
}

MainWindow::~MainWindow() {
	// TODO Auto-generated destructor stub
}

void MainWindow::display() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	for (auto view: g_view) {
		ViewInterface *i = view;
		i->display();
	}
	glutSwapBuffers();
}

void MainWindow::keyboard(unsigned char key, int x, int y) {
	key_focus->keyPressed(key);
	glutPostRedisplay();
}

void MainWindow::mouse(int button, int state, int x, int y) {
	mouse_focus->mouseClicked(button, state, x, wnd_height - y);
	glutPostRedisplay();
}

void MainWindow::displayCallback() {
	ins->display();
}

void MainWindow::keyboardCallback(unsigned char key, int x, int y) {
	ins->keyboard(key, x, y);
}

void MainWindow::mouseCallback(int button, int state, int x, int y) {
	ins->mouse(button, state, x, y);
}

void MainWindow::mouseCallbackMotionFunc(int x, int y) {
	ins->mouse(-1, -1, x, y);
}

} /* namespace std */
