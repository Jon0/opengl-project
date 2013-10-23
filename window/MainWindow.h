/*
 * MainWindow.h
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <map>
#include <memory>
#include <vector>
#include <chrono>
#include <string>
#include <GL/glut.h>

#include "../input/KeyListener.h"
#include "../input/MouseListener.h"
#include "../pipeline/Pipeline.h"
#include "../view/ViewInterface.h"

namespace std {

class MainWindow:
		public enable_shared_from_this<MainWindow> {
public:
	GLuint g_mainWnd;
	MainWindow(int, int, string);
	virtual ~MainWindow();

	virtual void start();
	void addView( shared_ptr<ViewInterface> );
	void setUpdateFunc( shared_ptr<Pipeline> );

private:
	int wnd_width, wnd_height;
	vector<shared_ptr<ViewInterface>> g_view;
	shared_ptr<Pipeline> pl;

	void display();
	void reshape(int, int);
	void keyboard(unsigned char, int, int);
	void mouseClick(int, int, int, int);
	void mouseDrag(int, int);

	/*
	 * static functions for glut
	 */
	static void displayCallback();
	static void reshapeCallback(int, int);
	static void keyboardCallback(unsigned char, int, int);
	static void mouseCallback(int button, int state, int x, int y);
	static void mouseCallbackMotionFunc(int x, int y);
	static void updateWindows();
};

extern map<int, shared_ptr<MainWindow>> instances;

} /* namespace std */
#endif /* MAINWINDOW_H_ */
