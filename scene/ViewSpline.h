/*
 * ViewSpline.h
 *
 *  Created on: 30/08/2013
 *      Author: remnanjona
 */

#ifndef VIEWSPLINE_H_
#define VIEWSPLINE_H_

#include "../animation/PointList.h"
#include "../view/Ortho.h"

namespace std {

class ViewSpline: public Ortho {
public:
	ViewSpline();
	virtual ~ViewSpline();
	virtual int mouseClicked(int, int, int, int);
	virtual int mouseDragged(int x, int y);
protected:
	bool play;
	float time;
	PointList *spline;
	virtual void display();
	virtual void messageSent(string);
};

} /* namespace std */
#endif /* VIEWSPLINE_H_ */
