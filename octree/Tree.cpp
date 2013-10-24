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

Tree::Tree(int l, shared_ptr<GRender> scene):
	root { 1 },
	location { [](GLuint i, GLint v){ glUniform1i(i, v); } },
	locationN { [](GLuint i, GLint v){ glUniform1i(i, v); } },
	locationX { [](GLuint i, GLint v){ glUniform1i(i, v); } },
	locationY { [](GLuint i, GLint v){ glUniform1i(i, v); } },
	locationZ { [](GLuint i, GLint v){ glUniform1i(i, v); } },
	locationXN { [](GLuint i, GLint v){ glUniform1i(i, v); } },
	locationYN { [](GLuint i, GLint v){ glUniform1i(i, v); } },
	locationZN { [](GLuint i, GLint v){ glUniform1i(i, v); } }
{
	levels = l;
	size = levels * levels * levels;
	unsigned int *texels = new unsigned int [size * 4];
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
	             GL_FLOAT, texels);

	//glGenerateMipmap(GL_TEXTURE_3D);

	glGenTextures(1, &addrN);
	glBindTexture(GL_TEXTURE_3D, addrN);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA8, levels, levels, levels, 0, GL_RGBA,
				GL_FLOAT, texels);

	//glGenerateMipmap(GL_TEXTURE_3D);


	// for each direction (from 6)
	// calc outgoing vec of light coming in that dir
	// in shader multiply each component of incoming light by the pre calc for that part

	glm::vec4 **d = new glm::vec4 *[6];
	d[0] = new glm::vec4 [size];
	d[1] = new glm::vec4 [size];
	d[2] = new glm::vec4 [size];
	d[3] = new glm::vec4 [size];
	d[4] = new glm::vec4 [size];
	d[5] = new glm::vec4 [size];
	makeNormals(scene, d);

	/*
	 * transfer data to textures
	 */
	for (int t = 0; t < 6; ++t) {
		for (unsigned int i = 0; i < levels; ++i) {
			for (unsigned int j = 0; j < levels; ++j) {
				for (unsigned int k = 0; k < levels; ++k) {
					int offset = (i + j * levels + k * levels * levels);
					glm::vec4 total = glm::vec4(0,0,0,0);
					if ( glm::length( d[t][offset] ) > 0 ) {
						total = glm::normalize( d[t][offset] );
						total.w = 1.0;
					}
					//cout << total.x << ", " << total.y << ", " << total.z << endl;

					unsigned char w = 128 + total.w * 128;
					unsigned char x = 128 + total.x * 128;
					unsigned char y = 128 + total.y * 128;
					unsigned char z = 128 + total.z * 128;
					texels[offset] = (w << 24) + (z << 16) + (y << 8) + x;
				}
			}
		}

		glGenTextures(1, &addrReflect[t]);
		glBindTexture(GL_TEXTURE_3D, addrReflect[t]);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, levels, levels, levels, 0, GL_RGBA,
		             GL_UNSIGNED_BYTE, texels);

		//glGenerateMipmap(GL_TEXTURE_3D);
	}

	glBindTexture(GL_TEXTURE_3D, 0);
	delete texels;
}

Tree::~Tree() {
	// TODO Auto-generated destructor stub
}

void Tree::makeNormals(shared_ptr<GRender> scene, glm::vec4 **out) {

	// check each poly
	for (shared_ptr<Geometry> &g : scene->content()) {
		int nm = g->numMesh();
		for (int m = 0; m < nm; ++m) {
			for (GPolygon &p : g->polygon(m)) {
				//glm::vec3 voxel = (glm::vec3(i, j, k) - glm::vec3(64,64,64)) * 4.0f;

				fillNormals(p, out);
			}
		}
	}
}

void Tree::fillNormals(GPolygon &p, glm::vec4 **out) {
	// pick random points on triangle surface
	// use more points on large triangles
	glm::vec3 p1 = p.data()[0].position;
	glm::vec3 p2 = p.data()[1].position;
	glm::vec3 p3 = p.data()[2].position;

	glm::vec3 d1 = p2 - p1;
	glm::vec3 d2 = p3 - p1;

	float ainc = 5.0 / glm::length(d1);
	float binc = 5.0 / glm::length(d2);

	glm::vec4 norm = glm::vec4(p.normal(), 0.0);

	for (float a = 0.01; a < 0.99; a += ainc) {
		for (float b = 0.01; a + b < 0.99; b += binc) {

			glm::vec3 center = p1 + (a * d1) + (b * d2);
			//cout << p1.x << ", " <<  p1.y << ", " <<  p1.z << endl;


			glm::ivec3 voxelPos = glm::ivec3(center / 16.0f + mid);
			int offset = (voxelPos.x + voxelPos.y * levels + voxelPos.z * levels * levels);

			if (glm::dot(norm, glm::vec4(1, 0, 0, 0)) < 0.0) {
				out[0][offset] += glm::normalize(glm::reflect(glm::vec4(1, 0, 0, 0), norm));
			}
			else {
				out[3][offset] += glm::normalize(glm::reflect(glm::vec4(-1, 0, 0, 0), norm));
			}

			if (glm::dot(norm, glm::vec4(0, 1, 0, 0)) < 0.0) {
				out[1][offset] += glm::normalize(glm::reflect(glm::vec4(0, 1, 0, 0), norm));
			}
			else {
				out[4][offset] += glm::normalize(glm::reflect(glm::vec4(0, -1, 0, 0), norm));
			}

			if (glm::dot(norm, glm::vec4(0, 0, 1, 0)) < 0.0) {
				out[2][offset] += glm::normalize(glm::reflect(glm::vec4(0, 0, 1, 0), norm));
			}
			else {
				out[5][offset] += glm::normalize(glm::reflect(glm::vec4(0, 0, -1, 0), norm));
			}
		}
	}
}

glm::vec3 Tree::getPoint( glm::vec3 in ) {
	glm::vec3 c = in;
	c /= 512.0;
	c += mid;
	return c;
}

void Tree::enable( GLuint i ) {
	glBindImageTexture(i, addr, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);
	glBindImageTexture(i+1, addrN, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA8);

	for (int j = 0; j < 6; ++j) {
		glActiveTexture(GL_TEXTURE0 + i + 2 + j);
		glBindTexture(GL_TEXTURE_3D, addrReflect[j]);
	}
	locationX.setV( i + 2 + 0 );
	locationY.setV( i + 2 + 1 );
	locationZ.setV( i + 2 + 2 );
	locationXN.setV( i + 2 + 3 );
	locationYN.setV( i + 2 + 4 );
	locationZN.setV( i + 2 + 5 );
}

void Tree::enableTex( Program &prg, GLuint i ) {
	glActiveTexture(GL_TEXTURE0 + i);
	glBindTexture(GL_TEXTURE_3D, addr);
	location.setV( i );
	//prg.setUniform( s, &location );

	glActiveTexture(GL_TEXTURE0 + i + 1);
	glBindTexture(GL_TEXTURE_3D, addrN);
	locationN.setV( i+1 );
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
