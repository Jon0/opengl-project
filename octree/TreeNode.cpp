/*
 * TreeNode.cpp
 *
 *  Created on: 7/10/2013
 *      Author: remnanjona
 */

#include "TreeNode.h"

namespace std {

TreeNode::TreeNode(int l): TreeNode(l, NULL) {}

TreeNode::TreeNode(int l, TreeNode *p):
		UBO<OctreeNode> { GL_ARRAY_BUFFER }
{
	level = l;
	parent = p;

	/*
	 * parent
	 */
	if (p) {
		data.parent = parent->gpuAddr;
	}
	else {
		data.parent = 0;
	}

	/*
	 * children
	 */
	if (level > 1) {
		for (int i = 0; i < 8; ++i) {
			children[i] = new TreeNode(level / 2, this);
			data.children[i] = children[i]->gpuAddr;
		}
	}
	else {
		for (int i = 0; i < 8; ++i) {
			data.children[i] = 0;
		}
	}
	gpuAddr = make_gpu_Addr();

	data.color = glm::vec4(1.0, 0.0, 0.0, 1.0);
	update();
}

TreeNode::~TreeNode() {
	// TODO Auto-generated destructor stub
}

void addLight() {
	// pass light in 6 directions
	// then diagonals if adjacent sides are open, so on..
}

} /* namespace std */
