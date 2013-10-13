/*
 * SpeedCurve.h
 *
 *  Created on: 14/09/2013
 *      Author: remnanjona
 */

#ifndef SPEEDCURVE_H_
#define SPEEDCURVE_H_

#include <memory>
#include "../scene/SceneInterface.h"
#include "../spline/Path.h"
#include "../view/Ortho.h"
#include "../window/MainWindow.h"

namespace std {

bool vec_comp_x(const glm::vec3 &, const glm::vec3 &);

class SpeedCurve:
		public enable_shared_from_this<SpeedCurve>,
		public SceneInterface {
public:
	SpeedCurve();
	virtual ~SpeedCurve();

	void reset();
	void calculateValues();
	void setTimeDisplay(float);
	float getSpeedValue(float);
	float getDistanceValue(float);
	float getTotalDistance();

	virtual vector< shared_ptr<Geometry> > &content();
	virtual void update( chrono::duration<double> );
	virtual void display( shared_ptr<ViewInterface> );
	virtual void displayUI();
	virtual void displayGeometry();
	virtual int mouseClicked(shared_ptr<ViewInterface>, int, int, int, int);
	virtual int mouseDragged(shared_ptr<ViewInterface>, int x, int y);
	virtual void messageSent(string);
	virtual void keyPressed(unsigned char);

	vector< shared_ptr<Geometry> > objects;
	shared_ptr<MainWindow> mWnd;
	shared_ptr<Ortho> view;
	Path speed;
	vector<float> values;
	vector<float> distance;
	float total_distance;
	float time;
	float values_dx;
	bool dragSelection;
	int selection, pmx, pmy;

};

} /* namespace std */
#endif /* SPEEDCURVE_H_ */
