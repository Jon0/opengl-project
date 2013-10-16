/*
 * TreeNode.h
 *
 *  Created on: 7/10/2013
 *      Author: remnanjona
 */

#ifndef TREENODE_H_
#define TREENODE_H_

#include "../shader/ShaderStructs.h"
#include "../shader/UBO.h"

namespace std {

class TreeNode: public UBO<OctreeNode> {
public:
	int level;
	GLuint64 gpuAddr;
	TreeNode *parent;
	TreeNode *children[8];


	TreeNode(int);
	TreeNode(int, TreeNode *);
	virtual ~TreeNode();

	void addLight();
};

} /* namespace std */
#endif /* TREENODE_H_ */
