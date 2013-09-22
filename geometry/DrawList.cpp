/*
 * DrawList.cpp
 *
 *  Created on: 19/09/2013
 *      Author: remnanjona
 */

#include <iostream>
#include "DrawList.h"

namespace std {

DrawList::DrawList(vector<GPolygon> shape, GLenum drawMode) {
	unsigned int s = shape.size();
	float *t = new float [s * 3 * 3];
	float *b = new float [s * 3 * 3];

	for (unsigned int i = 0; i < s; ++i) {
		for (unsigned int v = 0; v < 3; ++v) {
			t[i * 3 * 3 + v * 3 + 0] = shape.data()[i].data()[v].basis.v[0].v[0];
			t[i * 3 * 3 + v * 3 + 1] = shape.data()[i].data()[v].basis.v[0].v[1];
			t[i * 3 * 3 + v * 3 + 2] = shape.data()[i].data()[v].basis.v[0].v[2];
			b[i * 3 * 3 + v * 3 + 0] = shape.data()[i].data()[v].basis.v[1].v[0];
			b[i * 3 * 3 + v * 3 + 1] = shape.data()[i].data()[v].basis.v[1].v[1];
			b[i * 3 * 3 + v * 3 + 2] = shape.data()[i].data()[v].basis.v[1].v[2];
		}
	}

	glGenBuffers(1, &tangentbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
	glBufferData(GL_ARRAY_BUFFER, s * 3 * 3 * sizeof(float), t, GL_STATIC_DRAW);


	glGenBuffers(1, &bitangentbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
	glBufferData(GL_ARRAY_BUFFER, s * 3 * 3 * sizeof(float), b, GL_STATIC_DRAW);

	diffuseTex = NULL;
	normalTex = NULL;

	// Assign a display list; return 0 if err
	m_glGeomListPoly = glGenLists(1);
	glNewList(m_glGeomListPoly, GL_COMPILE);

	/*
	 * draw the shape
	 */
	glBegin(drawMode);
	for (unsigned int i = 0; i < shape.size(); ++i) {
		for (unsigned int v = 0; v < shape[i].size(); ++v) {
			float *uv = shape[i][v].getTexCoord().v;
			float *norm = shape[i][v].getNormal().v;
			float *pos = shape[i][v].getPosition().v;
			glTexCoord3fv(uv);
			glNormal3fv(norm);
			glVertex3fv(pos);
		}
	}
	glEnd();

	glEndList();
}

DrawList::~DrawList() {
	glDeleteLists(m_glGeomListPoly, 1);
}

void DrawList::display() {
	//glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	/* draw */
	glCallList(m_glGeomListPoly);
}

int DrawList::selectMouse(int, int) {
	return false;
}

void DrawList::setBumpMap(const char *diffuse, const char *bump, GLuint program) {
	diffuseTex = new Tex();
	diffuseTex->make2DTex(diffuse);
	normalTex = new Tex();
	normalTex->make2DTex(bump);

	DiffuseTextureID  = glGetUniformLocation(program, "DiffuseTextureSampler");
	NormalTextureID  = glGetUniformLocation(program, "NormalTextureSampler");
	SpecularTextureID  = glGetUniformLocation(program, "SpecularTextureSampler");
}

void DrawList::setupBump() {
	// Bind our diffuse texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture( GL_TEXTURE_2D, diffuseTex->getAddr() );
	// Set our "DiffuseTextureSampler" sampler to user Texture Unit 0
	glUniform1i(DiffuseTextureID, 0);

	// Bind our normal texture in Texture Unit 1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture( GL_TEXTURE_2D, normalTex->getAddr() );
	// Set our "Normal    TextureSampler" sampler to user Texture Unit 0
	glUniform1i(NormalTextureID, 1);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
	    0,                  // attribute
	    3,                  // size
	    GL_FLOAT,           // type
	    GL_FALSE,           // normalized?
	    0,                  // stride
	    (void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
	    1,                                // attribute
	    2,                                // size
	    GL_FLOAT,                         // type
	    GL_FALSE,                         // normalized?
	    0,                                // stride
	    (void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
	    2,                                // attribute
	    3,                                // size
	    GL_FLOAT,                         // type
	    GL_FALSE,                         // normalized?
	    0,                                // stride
	    (void*)0                          // array buffer offset
	);

	// 4th attribute buffer : tangents
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
	glVertexAttribPointer(
	    3,                                // attribute
	    3,                                // size
	    GL_FLOAT,                         // type
	    GL_FALSE,                         // normalized?
	    0,                                // stride
	    (void*)0                          // array buffer offset
	);

	// 5th attribute buffer : bitangents
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
	glVertexAttribPointer(
	    4,                                // attribute
	    3,                                // size
	    GL_FLOAT,                         // type
	    GL_FALSE,                         // normalized?
	    0,                                // stride
	    (void*)0                          // array buffer offset
	);
}

} /* namespace std */
