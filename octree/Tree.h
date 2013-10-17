/*
 * Tree.h
 *
 *  Created on: 7/10/2013
 *      Author: remnanjona
 */

#ifndef TREE_H_
#define TREE_H_

#include <memory>
#include <glm/glm.hpp>

#include "../geometry/Geometry.h"
#include "../scene/GRender.h"
#include "../shader/Program.h"
#include "../shader/UniformControl.h"
#include "TreeNode.h"

namespace std {

class Tree {
public:
	TreeNode root;
	GLuint addr, addrN, addrReflect [6];
	unsigned int levels;
	unsigned int size;
	glm::vec3 *normals;
	glm::vec3 mid;

	shared_ptr<Geometry> geom;
	UniformControl<GLint> location, locationN, locationX, locationY, locationZ, locationXN, locationYN, locationZN;

	Tree(int, shared_ptr<GRender>);
	virtual ~Tree();

	void makeNormals(shared_ptr<GRender>, glm::vec3 **);
	void fillNormals(GPolygon &, glm::vec3 **);
	glm::vec3 getPoint( glm::vec3 );
	void enable( GLuint );
	void enableTex( Program &, GLuint );
	void addLight();
	void calc(shared_ptr<Geometry>);
};

} /* namespace std */
#endif /* TREE_H_ */
