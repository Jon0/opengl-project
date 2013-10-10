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
#include "../shader/UniformControl.h"
#include "TreeNode.h"

namespace std {

struct innerNode {
	char child[15], far, contour[24];
	int validMask, leafMask, contourMask;
};

class Tree {
	TreeNode root;
	GLuint addr;
	unsigned int levels;
	unsigned int size;
	unsigned int *texels;
	glm::vec3 *normals;
	glm::vec3 mid;

	shared_ptr<Geometry> geom;

public:
	UniformControl<GLint> location;

	Tree(int, shared_ptr<Geometry>);
	virtual ~Tree();


	glm::vec3 getPoint( glm::vec3 );
	void enable(GLuint i);
	void addLight();
};

} /* namespace std */
#endif /* TREE_H_ */
