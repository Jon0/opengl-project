/*
 * TreeNode.h
 *
 *  Created on: 7/10/2013
 *      Author: remnanjona
 */

#ifndef TREENODE_H_
#define TREENODE_H_

namespace std {

struct innerNode {
	char child[15], far, contour[24];
	int validMask, leafMask, contourMask;
};

class TreeNode {
	TreeNode *parent;
	TreeNode *inner[8];

	// 26 adjacent directions

public:
	TreeNode();
	virtual ~TreeNode();

	void addLight();
};

} /* namespace std */
#endif /* TREENODE_H_ */
