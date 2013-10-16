/*
 * DrawList.h
 *
 *  Created on: 19/09/2013
 *      Author: remnanjona
 */

#ifndef SKELETONMESH_H_
#define SKELETONMESH_H_

#include <GL/glut.h>

#include "../texture/Tex.h"
#include "Geometry.h"
#include "GMesh.h"

namespace std {

class SkeletonMesh: public Geometry {
public:
	SkeletonMesh( vector<GMesh> );
	virtual ~SkeletonMesh();

	virtual void init(VertexBuffer *);
	virtual void update( UniformBlock<BoneProperties> & );
	virtual void draw();
	virtual void drawDebug();
	virtual vector<GPolygon> &polygon(int);
	virtual glm::mat4 transform();
	virtual void setTransform(glm::mat4);
	virtual int selectMouse( int, int );
	virtual UBO<MaterialProperties> *materialUBO();
	virtual MaterialProperties &material();
	virtual void updateMaterial();

	GMesh &getMesh(int);

	/*
	 * do these need to be kept?
	 */
	vector<GMesh> data;

	/* Transformation */
	glm::mat4 transform_matrix;

	/* Indices */
	GLuint *length;
	GLuint *elementbuffer;

	/* material */
	UBO<MaterialProperties> materialType;
};

} /* namespace std */
#endif /* SKELETONMESH_H_ */