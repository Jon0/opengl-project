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
#include "SceneInterface.h"
#include "SpeedCurve.h"
#include "../spline/Path.h"

namespace std {

class ViewInterface;

class ViewSpline: public SceneInterface {
public:
	ViewSpline();
	virtual ~ViewSpline();

	virtual void display( ViewInterface *, chrono::duration<double> );
	virtual int mouseClicked(ViewInterface *, int, int, int, int);
	virtual int mouseDragged(ViewInterface *, int x, int y);
	virtual void messageSent(string);
	virtual void keyPressed(unsigned char);

private:
	bool play;
	chrono::duration<double> time;

	ViewInterface *view;
	SpeedCurve sp;

	Teapot teapot;
	Path path;

	string message;
};

} /* namespace std */
#endif /* VIEWSPLINE_H_ */
