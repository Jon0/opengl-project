/*
 * V3D.h
 *
 *  Created on: 23/04/2013
 *      Author: remnanjona
 */

#ifndef V3D_H_
#define V3D_H_

#include <vector>
#include <glm/glm.hpp>

#include "../math/Basis.h"

namespace std {

class GVertex {
public:
	glm::vec3 position;
	glm::vec3 texCoord;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bitangent;

	GVertex();
	GVertex( Vec3D d );
	GVertex(float, float, float);
	GVertex(float, float, float, float, float, float, float, float, float);
	virtual ~GVertex();

	float getX();
	float getY();
	float getZ();

	glm::vec3 getPosition();
	glm::vec3 getNormal();
	glm::vec3 getTexCoord();

	void setPos(float x, float y, float z);
	void setNormal(float x, float y, float z);
	void setTexCoord(float x, float y, float z);

	void setNormal( float * );
	void setTexCoord( float * );

	void toArray( float *array, int offset );
	void print();
};

typedef vector<GVertex> GPolygon;

} /* namespace std */
#endif /* V3D_H_ */
