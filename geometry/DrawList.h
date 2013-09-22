/*
 * DrawList.h
 *
 *  Created on: 19/09/2013
 *      Author: remnanjona
 */

#ifndef DRAWLIST_H_
#define DRAWLIST_H_

#include <GL/glut.h>
#include "../texture/Tex.h"
#include "Drawable.h"
#include "GVertex.h"

namespace std {

class DrawList: public Drawable {
public:
	DrawList(vector<GPolygon>, GLenum);
	virtual ~DrawList();

	virtual void display();
	virtual int selectMouse(int, int);

	void setBumpMap(const char *, const char *, GLuint);
	void setupBump();

	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint tangentbuffer;
	GLuint bitangentbuffer;

	GLuint m_glGeomListPoly;

	Tex *diffuseTex;
	Tex *normalTex;

	GLuint DiffuseTextureID;
	GLuint NormalTextureID;
	GLuint SpecularTextureID;
};

} /* namespace std */
#endif /* DRAWLIST_H_ */
