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
map<int, MainWindow *> instances;

MainWindow::MainWindow(int width, int height) {
	wnd_width = width;
	wnd_height = height;
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(wnd_width, wnd_height);
	g_mainWnd = glutCreateWindow("COMP308 Assignment 3");
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);
	glutKeyboardFunc(keyboardCallback);
	glutMouseFunc(mouseCallback);
	glutMotionFunc(mouseCallbackMotionFunc);
	glutIdleFunc(idleFunc);

	/*
	 *	keep a reference to this instance
	 *	available from static methods
	 */
	instances[g_mainWnd] = this;

	// get initial time
	time = chrono::high_resolution_clock::now();
}

MainWindow::~MainWindow() {
	for (auto view: g_view) {
		delete view;
	}
}

void MainWindow::addView(ViewInterface *vi) {
	g_view.push_back(vi);
}

void MainWindow::display() {
	chrono::time_point<chrono::high_resolution_clock> newTime = chrono::system_clock::now();
	chrono::duration<double> tick = newTime - time;
	time = newTime;
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	for (auto &view: g_view) {
		((ViewInterface *) view )->setView( g_mainWnd, tick );
	}
	glutSwapBuffers();
}

void MainWindow::reshape(int x, int y) {
	for (auto view : g_view) {
		((ViewInterface *) view )->resize( g_mainWnd, x, y);
	}
	wnd_width = x;
	wnd_height = y;
	glViewport(0, 0, wnd_width, wnd_height);
}

void MainWindow::keyboard(unsigned char key, int x, int y) {
	for (auto view: g_view) {
		((ViewInterface *) view )->keyPressed( g_mainWnd, key);
		//if (((ViewInterface *) view )->keyPressed(key)) break;
	}
	//glutPostRedisplay();
}

// TODO: send GLuint of window
void MainWindow::mouseClick(int button, int state, int x, int y) {
	for (auto view: g_view) {
		if (((ViewInterface *) view )->mouseClicked( g_mainWnd, button, state, x, wnd_height - y)) break;
	}
	//glutPostRedisplay();
}

void MainWindow::mouseDrag(int x, int y) {
	for (auto view: g_view) {
		if (((ViewInterface *) view )->mouseDragged( g_mainWnd, x, wnd_height - y)) break;
	}
	//glutPostRedisplay();
}

void MainWindow::displayCallback() {
	MainWindow *ins = instances[ glutGetWindow() ];
	ins->display();
}

void MainWindow::reshapeCallback(int x, int y) {
	MainWindow *ins = instances[ glutGetWindow() ];
	ins->reshape(x, y);
}

void MainWindow::keyboardCallback(unsigned char key, int x, int y) {
	MainWindow *ins = instances[ glutGetWindow() ];
	ins->keyboard(key, x, y);
}

void MainWindow::mouseCallback(int button, int state, int x, int y) {
	MainWindow *ins = instances[ glutGetWindow() ];
	ins->mouseClick(button, state, x, y);
}

void MainWindow::mouseCallbackMotionFunc(int x, int y) {
	MainWindow *ins = instances[ glutGetWindow() ];
	ins->mouseDrag(x, y);
}

void MainWindow::idleFunc() {
	glutPostRedisplay();
}

} /* namespace std */
