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

#include "../geometry/Teapot.h"
#include "../scene/SceneInterface.h"
#include "../spline/Path.h"

namespace std {

class ViewInterface;

class ViewSpline: public SceneInterface {
public:
	ViewSpline();
	virtual ~ViewSpline();

	int clickPrimary(int button, int state, int x, int y);
	int clickSecondary(int button, int state, int x, int y);

	virtual void display( ViewInterface *, chrono::duration<double> );
	virtual int mouseClicked(ViewInterface *, int, int, int, int);
	virtual int mouseDragged(ViewInterface *, int x, int y);
	virtual void messageSent(string);

private:
	ViewInterface *view, *acc;
	string message;
	Teapot teapot;
	Path path;
	Path speed;

};

} /* namespace std */
#endif /* VIEWSPLINE_H_ */
