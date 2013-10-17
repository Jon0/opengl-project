/*
 * Geometry.h
 *
 *  Created on: 12/09/2013
 *      Author: remnanjona
 */

#include <glm/glm.hpp>

#include "../buffer/VertexBuffer.h"
#include "../shader/UBO.h"
#include "../shader/ShaderStructs.h"
#include "../shader/UniformBlock.h"
#include "GPolygon.h"

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

namespace std {

class Geometry {
public:
	virtual ~Geometry() {}
	virtual void init(VertexBuffer *) = 0;
	virtual void update( UniformBlock<BoneProperties> & ) = 0;
	virtual void draw() = 0;
	virtual void drawDebug() = 0;
	virtual int numMesh() = 0;
	virtual vector<GPolygon> &polygon(int) = 0;
	virtual glm::mat4 transform() = 0;
	virtual void setTransform(glm::mat4) = 0;
	virtual UBO<MaterialProperties> *materialUBO() = 0;
	virtual MaterialProperties &material() = 0;
	virtual void updateMaterial() = 0;
};

} /* namespace std */
#endif /* GEOMETRY_H_ */
