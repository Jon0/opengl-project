/*
 * SpeedCurve.h
 *
 *  Created on: 14/09/2013
 *      Author: remnanjona
 */

#ifndef SPEEDCURVE_H_
#define SPEEDCURVE_H_

#include "../scene/SceneInterface.h"
#include "../spline/Path.h"

namespace std {

bool vec_comp_x(Vec3D, Vec3D);

class SpeedCurve: public SceneInterface {
public:
	SpeedCurve();
	virtual ~SpeedCurve();

	void calculateValues();

	virtual void display( ViewInterface *, chrono::duration<double> );
	virtual int mouseClicked(ViewInterface *, int, int, int, int);
	virtual int mouseDragged(ViewInterface *, int x, int y);
	virtual void messageSent(string);

private:
	float values_dx;
	vector<float> values;


	ViewInterface *view;
	Path speed;


};

} /* namespace std */
#endif /* SPEEDCURVE_H_ */
