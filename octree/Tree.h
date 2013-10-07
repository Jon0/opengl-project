/*
 * Tree.h
 *
 *  Created on: 7/10/2013
 *      Author: remnanjona
 */

#ifndef TREE_H_
#define TREE_H_

#include "TreeNode.h"

namespace std {

struct innerNode {
	char child[15], far, contour[24];
	int validMask, leafMask, contourMask;
};

class Tree {
	TreeNode root;

public:
	Tree();
	virtual ~Tree();
};

} /* namespace std */
#endif /* TREE_H_ */
