/*
 * ViewSpline.h
 *
 *  Created on: 30/08/2013
 *      Author: remnanjona
 */

#ifndef VIEWSPLINE_H_
#define VIEWSPLINE_H_

#include <memory>
#include <vector>
#include <chrono>

#include "../geometry/Teapot.h"
#include "SceneInterface.h"
#include "SpeedCurve.h"
#include "../spline/Path.h"

namespace std {

class ViewInterface;

class ViewSpline:
		public enable_shared_from_this<ViewSpline>,
		public SceneInterface {
public:
	ViewSpline();
	virtual ~ViewSpline();

	virtual void prepare();
	virtual void display( shared_ptr<ViewInterface>, chrono::duration<double> );
	virtual int mouseClicked(shared_ptr<ViewInterface>, int, int, int, int);
	virtual int mouseDragged(shared_ptr<ViewInterface>, int x, int y);
	virtual void messageSent(string);
	virtual void keyPressed(unsigned char);

private:
	shared_ptr<MainWindow> mWnd;
	shared_ptr<ViewInterface> view;
	shared_ptr<Teapot> teapot;

	bool play;
	chrono::duration<double> time;

	SpeedCurve sp;
	Path path;
	string message;
};

} /* namespace std */
#endif /* VIEWSPLINE_H_ */
