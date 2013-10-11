/*
 * Spline.h
 *
 *  Created on: 29/08/2013
 *      Author: remnanjona
 */

#ifndef SPLINE_H_
#define SPLINE_H_

#include <vector>
#include <glm/glm.hpp>

#include "../math/PointArray.h"
#include "../math/Vec3D.h"

namespace std {

class Spline {
public:
	Spline();
	virtual ~Spline() {};
	float getULength();
	float getArcLength();
	glm::vec3 getPoint(float);
	glm::vec3 getDistPoint(float);
	float calcPointInc(float, float);
	void displayline();
	void equaliseLength();
	virtual glm::vec3 getKeyPoint(int) = 0;
	virtual int getNumKeyFrames() = 0;

protected:
	glm::vec3 catmull_rom(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, float u);
	float spline_length;
	PointArray<float> distance;
};

} /* namespace std */
#endif /* SPLINE_H_ */
