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
	virtual int mouseClicked(int, int, int, int);
	virtual int mouseDragged(int x, int y);
	void display(GLuint, chrono::duration<double>);
protected:
	MainWindow primary;
	Drawable *d;
	Path path;
	virtual void messageSent(string);
};

} /* namespace std */
#endif /* VIEWSPLINE_H_ */
