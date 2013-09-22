/*
 * DrawList.cpp
 *
 *  Created on: 19/09/2013
 *      Author: remnanjona
 */

#include <iostream>
#include "DrawList.h"

namespace std {

DrawList::DrawList(vector<GPolygon> shape) {
	s = shape.size();
	float *p = new float [s * 3 * 3];
	float *c = new float [s * 3 * 2];
	float *n = new float [s * 3 * 3];
	float *t = new float [s * 3 * 3];
	float *b = new float [s * 3 * 3];

	for (unsigned int i = 0; i < s; ++i) {
		for (unsigned int v = 0; v < 3; ++v) {
			p[i * 3 * 3 + v * 3 + 0] = shape.data()[i].data()[v].e[POS].v[0];
			p[i * 3 * 3 + v * 3 + 1] = shape.data()[i].data()[v].e[POS].v[1];
			p[i * 3 * 3 + v * 3 + 2] = shape.data()[i].data()[v].e[POS].v[2];

			c[i * 3 * 2 + v * 2 + 0] = shape.data()[i].data()[v].e[UV].v[0];
			c[i * 3 * 2 + v * 2 + 1] = shape.data()[i].data()[v].e[UV].v[1];

			n[i * 3 * 3 + v * 3 + 0] = shape.data()[i].data()[v].e[NORM].v[0];
			n[i * 3 * 3 + v * 3 + 1] = shape.data()[i].data()[v].e[NORM].v[1];
			n[i * 3 * 3 + v * 3 + 2] = shape.data()[i].data()[v].e[NORM].v[2];

			t[i * 3 * 3 + v * 3 + 0] = shape.data()[i].data()[v].basis.v[0].v[0];
			t[i * 3 * 3 + v * 3 + 1] = shape.data()[i].data()[v].basis.v[0].v[1];
			t[i * 3 * 3 + v * 3 + 2] = shape.data()[i].data()[v].basis.v[0].v[2];
			b[i * 3 * 3 + v * 3 + 0] = shape.data()[i].data()[v].basis.v[1].v[0];
			b[i * 3 * 3 + v * 3 + 1] = shape.data()[i].data()[v].basis.v[1].v[1];
			b[i * 3 * 3 + v * 3 + 2] = shape.data()[i].data()[v].basis.v[1].v[2];
		}
	}

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, s * 3 * 3 * sizeof(float), p, GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, s * 3 * 2 * sizeof(float), c, GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, s * 3 * 3 * sizeof(float), n, GL_STATIC_DRAW);

	glGenBuffers(1, &tangentbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
	glBufferData(GL_ARRAY_BUFFER, s * 3 * 3 * sizeof(float), t, GL_STATIC_DRAW);


	glGenBuffers(1, &bitangentbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
	glBufferData(GL_ARRAY_BUFFER, s * 3 * 3 * sizeof(float), b, GL_STATIC_DRAW);

	/* the order verticies get drawn */
	std::vector<unsigned int> indices;
	int off = 0;
	for (unsigned int i = 0; i < shape.size(); ++i) {
		for (unsigned int v = 0; v < 3; ++v) {
			indices.push_back(off);
			off++;
		}
	}

	// Generate a buffer for the indices
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	/* default disable texturing */
	diffuseTex = NULL;
	normalTex = NULL;
	DiffuseTextureID  = 0;
	NormalTextureID  = 0;
	SpecularTextureID = 0;

	/* not compiled yet */
	m_glGeomListPoly = 0;
}

DrawList::~DrawList() {
	glDeleteLists(m_glGeomListPoly, 1);
}

void DrawList::display() {
	glCallList(m_glGeomListPoly);
}

int DrawList::selectMouse(int, int) {
	return false;
}

void DrawList::compile(GLenum drawMode) {
	// Assign a display list; return 0 if err
	m_glGeomListPoly = glGenLists(1);
	glNewList(m_glGeomListPoly, GL_COMPILE);

	/* settings */
	//glEnable(GL_NORMALIZE);
	//glShadeModel(GL_SMOOTH);

	/*
	 * draw the shape
	 */
	setupBump();

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	// Draw the triangles !
	glDrawElements( drawMode, s * 3, GL_UNSIGNED_INT, 0 );

	glEndList();
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

	/*
	 * TODO only setup these if needed
	 */
	if (diffuseTex && normalTex) {

		// Bind our diffuse texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTex->getAddr());
		// Set our "DiffuseTextureSampler" sampler to user Texture Unit 0
		glUniform1i(DiffuseTextureID, 0);

		// Bind our normal texture in Texture Unit 1
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalTex->getAddr());
		// Set our "Normal    TextureSampler" sampler to user Texture Unit 0
		glUniform1i(NormalTextureID, 1);

		// 4th attribute buffer : tangents
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
		glVertexAttribPointer(3,                                // attribute
				3,                                // size
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*) 0                          // array buffer offset
				);

		// 5th attribute buffer : bitangents
		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
		glVertexAttribPointer(4,                                // attribute
				3,                                // size
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*) 0                          // array buffer offset
				);
	}
}

} /* namespace std */
