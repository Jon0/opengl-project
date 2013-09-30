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
#include <vector>
#include <GL/gl.h>

#include "Shader.h"
#include "UniformBlock.h"
#include "UniformControl.h"
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

	/*
	 * attached uniforms
	 */
	map<string, GLuint> uniformName;
	map<GLuint, UniformControlBase *> uniformControl;

public:
	Program(string);
	virtual ~Program();

	/*
	 * set a uniform to match a control value, the uniform is automatically
	 * updated when calling enable()
	 */
	template<class T> void setUniform(string name, UniformControl<T> *c) {
		auto value = uniformName.find(name);	// check for existing value
		if (value == uniformName.end()) {
			GLuint id = glGetUniformLocation(programID, name.c_str());
			uniformName[name] = id;
			uniformControl[id] = c;
		}
		else {
			uniformControl.at( uniformName[name] ) = c;
		}
	}

	template<class T> UniformBlock<T> getBlock(string name, int length) {
		return UniformBlock<T>(programID, name, length);
	}

	void enable();
	void disable();

	/* TODO remove this */
	GLuint addUniform(string);
};

extern Program *active;

} /* namespace std */
#endif /* PROGRAM_H_ */
