/*
 * Voxelize.cpp
 *
 *  Created on: 12/10/2013
 *      Author: remnanjona
 */

#include "Voxelize.h"

namespace std {

Voxelize::Voxelize( shared_ptr<SceneInterface> s ):
		vox { "voxelization" },
		scene { s }
{

}

Voxelize::~Voxelize() {}

Program &Voxelize::getProgram() {
	return vox;
}

void Voxelize::update( chrono::duration<double> ) {
	vox.enable();
	glViewport(0, 0, 128, 128);
	glDisable(GL_DEPTH_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	for ( auto &g: scene->content() ) {
		g->draw();
	}

	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

void Voxelize::run( shared_ptr<ViewInterface> ) {

}

} /* namespace std */
