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
		scene { s },
		location { [](GLuint i, GLint v){ glUniform1i(i, v); } }
{
//	glGenTextures(1, &addr);
//	glBindTexture(GL_TEXTURE_3D, addr);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
//	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, levels, levels, levels, 0, GL_RGBA,
//	             GL_UNSIGNED_BYTE, texels);
//
//	glBindImageTexture()

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
