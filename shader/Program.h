/*
 * Program.h
 *
 *  Created on: 23/09/2013
 *      Author: remnanjona
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <map>
#include <memory>
#include <GL/gl.h>

#include "Shader.h"
#include "../buffer/VertexBuffer.h"
#include "../geometry/Geometry.h"
#include "../texture/Tex.h"


namespace std {

class Program {
private:
	/*
	 * shaders
	 */
	GLuint programID;
	Shader vert;
	Shader frag;

	map<string, GLuint> uniform;

public:
	Program(string);
	virtual ~Program();

	GLuint addUniform(string);
	GLuint getUniform(string);
	void setup( shared_ptr<Geometry> d );
	void enable();
};

} /* namespace std */
#endif /* PROGRAM_H_ */
