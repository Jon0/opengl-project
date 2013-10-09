/*
 * Tree.h
 *
 *  Created on: 7/10/2013
 *      Author: remnanjona
 */

#ifndef TREE_H_
#define TREE_H_

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

public:
	UniformControl<GLint> location;

	Tree(int);
	virtual ~Tree();

	void enable(GLuint i);
};

} /* namespace std */
#endif /* TREE_H_ */
