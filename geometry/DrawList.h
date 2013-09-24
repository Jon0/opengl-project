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
#include "Geometry.h"
#include "GVertex.h"

namespace std {

class DrawList: public Geometry {
public:
	DrawList( vector<GPolygon> );
	virtual ~DrawList();

	virtual void init(VertexBuffer *);
	virtual void draw();

	virtual int selectMouse( int, int );

	void compile( GLenum );
	void setBumpMap( const char *, const char *, GLuint );
	void setupBump();

	/*
	 * do these need to be kept?
	 */
	unsigned int s;
	vector<GPolygon> data;

	/* Indices */
	GLuint elementbuffer;

	/* Buffers */
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint tangentbuffer;
	GLuint bitangentbuffer;

	/* Textures */
	Tex *diffuseTex;
	Tex *normalTex;
	GLuint DiffuseTextureID;
	GLuint NormalTextureID;
	GLuint SpecularTextureID;
};

} /* namespace std */
#endif /* DRAWLIST_H_ */
