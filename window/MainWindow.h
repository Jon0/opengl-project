/*
 * MainWindow.h
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <vector>
#include "../view/ViewInterface.h"

namespace std {

class MainWindow {
public:
	MainWindow();
	void display();
	virtual ~MainWindow();
protected:
	vector<ViewInterface *> g_view;
	GLuint g_mainWnd;
private:
	static void displayCallback();
};

} /* namespace std */
#endif /* MAINWINDOW_H_ */
