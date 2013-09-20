/*
 * Shader.cpp
 *
 *  Created on: 20/09/2013
 *      Author: remnanjona
 */

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <GL/glut.h>
#include "Shader.h"

namespace std {

Shader::Shader(const char *filename, GLenum type) {
	// load the fragment shader.
	fstream fragmentShaderFile(filename, std::ios::in);
	string fragmentShaderSource;
	if (fragmentShaderFile.is_open()) {
		stringstream buffer;
		buffer << fragmentShaderFile.rdbuf();
		fragmentShaderSource = buffer.str();
	}

	ShaderHandle = glCreateShader(type);
	const char *g = fragmentShaderSource.c_str();
	glShaderSource(ShaderHandle, 1, &g, NULL);
	glCompileShader(ShaderHandle);

	//Error checking.
	int result;
	glGetShaderiv(ShaderHandle, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		GLint blen = 0;
		GLsizei slen = 0;
		glGetShaderiv(ShaderHandle, GL_INFO_LOG_LENGTH , &blen);
		if (blen > 1)
		{
		 GLchar* compiler_log = (GLchar*)malloc(blen);
		 glGetInfoLogARB(ShaderHandle, blen, &slen, compiler_log);
		 cout << filename  << " compiler_log " << ":\n" << compiler_log;
		 free (compiler_log);
		}
	}
}

Shader::~Shader() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
