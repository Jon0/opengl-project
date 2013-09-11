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
#include "../spline/Spline.h"
#include "../view/Ortho.h"

namespace std {

class ViewSpline: public Ortho, public Spline {
public:
	ViewSpline();
	virtual ~ViewSpline();
	virtual int mouseClicked(int, int, int, int);
	virtual int mouseDragged(int x, int y);
	virtual Vec3D getKeyPoint(int);
	virtual int getNumKeyFrames();
protected:
	bool play;
	vector<Vec3D> points;
	float time_f;
	chrono::duration<double> time;
	virtual void display(chrono::duration<double>);
	virtual void messageSent(string);
};

} /* namespace std */
#endif /* VIEWSPLINE_H_ */
