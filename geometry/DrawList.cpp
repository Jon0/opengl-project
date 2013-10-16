/*
 * DrawList.cpp
 *
 *  Created on: 19/09/2013
 *      Author: remnanjona
 */

#include <iostream>
#include "DrawList.h"

namespace std {

DrawList::DrawList(vector<GMesh> shape) {
	data = shape;
	elementbuffer = 0;

	transform_matrix = glm::mat4(1.0f);

	//glm::vec3 color =  glm::normalize(glm::vec3(rand() % 256, rand() % 256, rand() % 256));
	glm::vec3 color =  glm::normalize(glm::vec3(1, 1, 1));
	materialType.data.AmbientColor = glm::vec4(color.x, color.y, color.z, 1.0);
	materialType.data.DiffuseColor = glm::vec4(color.x, color.y, color.z, 1.0);
	materialType.data.SpecularColor = glm::vec4(color.x / 5, color.y / 5, color.z / 5, 1.0);
	materialType.data.Exponent = 8.0;
	materialType.update();

	length = NULL;
	elementbuffer = NULL;
}

DrawList::~DrawList() {}

void DrawList::init(VertexBuffer *vb) {
	/* the order verticies get drawn */
	std::vector<unsigned int> indices;

	length = new GLuint [ data.size() ];
	GLuint *offset = new GLuint [ data.size() + 1 ];
	offset[0] = 0;
	int m = 0, off = vb->size();

	vector<GVertex> verts;

	for (GMesh mesh : data) {
		length[m] = 0;

		for (GPolygon poly : mesh) {
			for (GVertex vert : poly) {
				verts.push_back(vert);
				indices.push_back(off);
				off++;
				length[m]++;
			}

		}
		offset[m+1] = offset[m] + length[m];
		m++;
	}
	vb->add(verts);

	elementbuffer = new GLuint [ data.size() ];

	// Generate a buffer for the indices
	glGenBuffers(data.size(), elementbuffer);
	for (unsigned int i = 0; i < data.size(); ++i) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, length[i] * sizeof(unsigned int), &indices[ offset[i] ], GL_STATIC_DRAW);
	}
	delete offset;
}

void DrawList::draw() {
	for (unsigned int i = 0; i < data.size(); ++i) {
		// bind texture
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, data.data()[i].texaddr);

		// bind indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[i]);

		// output list
		glDrawElements(GL_TRIANGLES, length[i], GL_UNSIGNED_INT, 0);
	}
}

void DrawList::drawDebug() {
	for (GMesh mesh : data) {
		for (GPolygon poly : mesh) {
			for (GVertex vert : poly) {
				glBegin(GL_LINES);
				glColor3f(1, 0, 0);
				glVertex3fv(&vert.position[0]);
				glVertex3fv(&(vert.position + vert.normal)[0]);
				glColor3f(0, 1, 0);
				glVertex3fv(&vert.position[0]);
				glVertex3fv(&(vert.position + vert.tangent)[0]);
				glColor3f(0, 0, 1);
				glVertex3fv(&vert.position[0]);
				glVertex3fv(&(vert.position + vert.bitangent)[0]);
				glEnd();
			}
		}
	}
}

  // void DrawList::drawSkinnning(){
  //   /**
  //      should I do this here??
  //   **/
  // }


vector<GPolygon> &DrawList::polygon(int mesh) {
	return data.data()[mesh];
}

int DrawList::selectMouse(int, int) {
	return false;
}

glm::mat4 DrawList::transform() {
	return transform_matrix;
}

void DrawList::setTransform(glm::mat4 t) {
	transform_matrix = t;
}

UBO<MaterialProperties> *DrawList::materialUBO() {
	return &materialType;
}

MaterialProperties &DrawList::material() {
	return materialType.data;
}

void DrawList::updateMaterial() {
	return materialType.update();
}

GMesh &DrawList::getMesh(int i) {
	return data.data()[i];
}

} /* namespace std */
