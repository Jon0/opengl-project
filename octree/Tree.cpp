/*
 * Tree.cpp
 *
 *  Created on: 7/10/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <GL/gl.h>

#include "Tree.h"

namespace std {

Tree::Tree(int l):
	location { [](GLuint i, GLint v){ glUniform1i(i, v); } }
{
	levels = l;
	size = levels * levels * levels;
	texels = new unsigned int [size];
	normals = new glm::vec3 [size];
	int h = levels / 2;
	mid = glm::vec3(h, h, h);

	for (unsigned int i = 0; i < levels; ++i) {
		for (unsigned int j = 0; j < levels; ++j) {
			for (unsigned int k = 0; k < levels; ++k) {
				int offset = (i + j * levels + k * levels * levels);

				//float f = glm::distance(mid, glm::vec3(i, j, k));
				//unsigned char r = (int)(256.0 * (1 / f));
				unsigned char r = 0;
				texels[offset] = (255 << 24) + (r << 16) + (r << 8) + r;
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

	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA8, levels, levels, levels, 0, GL_RGBA,
	             GL_UNSIGNED_BYTE, texels);

	//glTexStorage3D(GL_TEXTURE_3D, 1, GL_RGBA8, levels, levels, levels);
	glBindTexture(GL_TEXTURE_3D, 0);
}

Tree::~Tree() {
	// TODO Auto-generated destructor stub
}

glm::vec3 Tree::getPoint( glm::vec3 in ) {
	glm::vec3 c = in;
	c /= 512.0;
	c += mid;
	return c;
}

void Tree::enable( GLuint i ) {
	glBindImageTexture(i, addr, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);
}

void Tree::enableTex( Program &prg, string s, GLuint i ) {
	glActiveTexture(GL_TEXTURE0 + i);
	glBindTexture(GL_TEXTURE_3D, addr);
	location.setV( i );
	prg.setUniform( s, &location );
}

void Tree::addLight() {
	// add light to octree root
}

void Tree::calc(shared_ptr<Geometry> g) {
	// TODO another texture for normals of each voxel
	vector<GPolygon> &gp = g->polygon(0);
	for (GPolygon &p: gp) {
		glm::vec3 c = getPoint( p.center() );
		int i = c.x, j = c.y, k = c.z;
		normals[i + j * levels + k * levels * levels] += p.normal();
	}
}

} /* namespace std */
