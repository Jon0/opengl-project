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

bool vec_comp_x(const Vec3D &, const Vec3D &);

class SpeedCurve: public SceneInterface {
public:
	SpeedCurve();
	virtual ~SpeedCurve();

	void calculateValues();
	void setTimeDisplay(float);
	float getSpeedValue(float);
	float getDistanceValue(float);
	float getTotalDistance();

	virtual void display( ViewInterface *, chrono::duration<double> );
	virtual int mouseClicked(ViewInterface *, int, int, int, int);
	virtual int mouseDragged(ViewInterface *, int x, int y);
	virtual void messageSent(string);
	virtual void keyPressed(unsigned char);

private:
	float total_distance;
	float time;
	float values_dx;
	vector<float> values;
	vector<float> distance;
	ViewInterface *view;
	Path speed;
};

} /* namespace std */
#endif /* SPEEDCURVE_H_ */
