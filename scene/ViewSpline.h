/*
 * ViewSpline.h
 *
 *  Created on: 30/08/2013
 *      Author: remnanjona
 */

#ifndef VIEWSPLINE_H_
#define VIEWSPLINE_H_

#include "../geometry/Spline.h"
#include "../view/Ortho.h"

namespace std {

class ViewSpline: public Ortho {
public:
	ViewSpline(int, int);
	virtual ~ViewSpline();
	virtual int mouseClicked(int, int, int, int);
protected:
	bool play;
	float time;
	Spline *spline;
	virtual void display();
	virtual void messageSent(string);
};

} /* namespace std */
#endif /* VIEWSPLINE_H_ */
