/*
 * Tree.cpp
 *
 *  Created on: 7/10/2013
 *      Author: remnanjona
 */

#include <GL/gl.h>

#include "Tree.h"

namespace std {

Tree::Tree(int l):
	location { [](GLuint i, GLint v){ glUniform1i(i, v); } }
{
	levels = l;
	size = levels * levels * levels;
	texels = new unsigned int [size];
	for (unsigned int i = 0; i < levels; ++i) {
		for (unsigned int j = 0; j < levels; ++j) {
			for (unsigned int k = 0; k < levels; ++k) {
				unsigned char r = 80; //3 % 256;
				texels[i + j * levels + k * levels * levels] = (255 << 24) + (r << 16) + (r << 8) + r;

			}
		}
	}

	glGenTextures(1, &addr);
	glBindTexture(GL_TEXTURE_3D, addr);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, levels, levels, levels, 0, GL_RGBA,
	             GL_UNSIGNED_BYTE, texels);

	// TODO another texture for normals of each voxel

}

Tree::~Tree() {
	// TODO Auto-generated destructor stub
}

void Tree::enable(GLuint i) {
	//for (unsigned int i = 0; i < levels; ++i) {
	//	for (unsigned int j = 0; j < levels; ++j) {
	//		for (unsigned int k = 0; k < levels; ++k) {
	//			unsigned char r = rand() % 256;
	//			texels[i + j * levels + k * levels * levels] = (255 << 24) + (r << 16) + (r << 8) + r;
	//
	//		}
	//	}
	//}


	glActiveTexture(GL_TEXTURE0 + i);
	glBindTexture(GL_TEXTURE_3D, addr);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, levels, levels, levels, 0, GL_RGBA,
	             GL_UNSIGNED_BYTE, texels);
	location.setV( i );
}

} /* namespace std */
