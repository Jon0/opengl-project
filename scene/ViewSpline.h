/*
 * ViewSpline.h
 *
 *  Created on: 30/08/2013
 *      Author: remnanjona
 */

#ifndef VIEWSPLINE_H_
#define VIEWSPLINE_H_

#include <vector>
#include <chrono>
#include "../window/MainWindow.h"
#include "../geometry/Drawable.h"
#include "../spline/Path.h"
#include "../view/Ortho.h"

namespace std {

class ViewSpline: public Ortho {
public:
	ViewSpline();
	virtual ~ViewSpline();
	virtual int mouseClicked(GLuint, int, int, int, int);
	int clickPrimary(int button, int state, int x, int y);
	int clickSecondary(int button, int state, int x, int y);
	virtual int mouseDragged(GLuint, int x, int y);
	void display(GLuint, chrono::duration<double>);
protected:
	MainWindow primary;
	Drawable *d;
	Path path;
	Path speed;
	virtual void messageSent(string);
};

} /* namespace std */
#endif /* VIEWSPLINE_H_ */
