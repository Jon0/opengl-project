/*
 * MainWindow.cpp
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#include <GL/glut.h>
#include "MainWindow.h"

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
	glutReshapeFunc(reshapeCallback);
	glutKeyboardFunc(keyboardCallback);
	glutMouseFunc(mouseCallback);
	glutMotionFunc(mouseCallbackMotionFunc);
	glutIdleFunc(idleFunc);

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
		((ViewInterface *) view )->resize(x, y);
	}
	wnd_width = x;
	wnd_height = y;
	glViewport(0, 0, wnd_width, wnd_height);
}

void MainWindow::keyboard(unsigned char key, int x, int y) {
	for (auto view: g_view) {
		((ViewInterface *) view )->keyPressed(key);
		//if (((ViewInterface *) view )->keyPressed(key)) break;
	}
	//glutPostRedisplay();
}

// TODO: send GLuint of window
void MainWindow::mouseClick(int button, int state, int x, int y) {
	for (auto view: g_view) {
		if (((ViewInterface *) view )->mouseClicked(button, state, x, wnd_height - y)) break;
	}
	//glutPostRedisplay();
}

void MainWindow::mouseDrag(int x, int y) {
	for (auto view: g_view) {
		if (((ViewInterface *) view )->mouseDragged(x, wnd_height - y)) break;
	}
	//glutPostRedisplay();
}

void MainWindow::displayCallback() {
	ins->display();
}

void MainWindow::reshapeCallback(int x, int y) {
	ins->reshape(x, y);
}

void MainWindow::keyboardCallback(unsigned char key, int x, int y) {
	ins->keyboard(key, x, y);
}

void MainWindow::mouseCallback(int button, int state, int x, int y) {
	ins->mouseClick(button, state, x, y);
}

void MainWindow::mouseCallbackMotionFunc(int x, int y) {
	ins->mouseDrag(x, y);
}

void MainWindow::idleFunc() {
	glutPostRedisplay();
}

} /* namespace std */
