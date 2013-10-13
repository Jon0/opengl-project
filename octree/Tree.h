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
#include "../shader/Program.h"
#include "../shader/UniformControl.h"
#include "TreeNode.h"

namespace std {

class Tree {
	TreeNode root;
	GLuint addr;
	unsigned int levels;
	unsigned int size;
	float *texels;
	glm::vec3 *normals;
	glm::vec3 mid;

	shared_ptr<Geometry> geom;

public:
	UniformControl<GLint> location, image;

	Tree(int);
	virtual ~Tree();


	glm::vec3 getPoint( glm::vec3 );
	void enable( Program &, GLuint );
	void addLight();
	void calc(shared_ptr<Geometry>);
};

} /* namespace std */
#endif /* TREE_H_ */
