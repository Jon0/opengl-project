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

Shader::Shader(char *filename) {
	// load the fragment shader.
	fstream fragmentShaderFile(filename, std::ios::in);
	string fragmentShaderSource;
	if (fragmentShaderFile.is_open()) {
		stringstream buffer;
		buffer << fragmentShaderFile.rdbuf();
		fragmentShaderSource = buffer.str();
	}

	GLuint fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	const char *g = fragmentShaderSource.c_str();
	glShaderSource(fragmentShaderObject, 1, &g, NULL);
	glCompileShader(fragmentShaderObject);

	//Error checking.
	int result;
	glGetShaderiv(fragmentShaderObject, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		GLint blen = 0;
		GLsizei slen = 0;
		glGetShaderiv(fragmentShaderObject, GL_INFO_LOG_LENGTH , &blen);
		if (blen > 1)
		{
		 GLchar* compiler_log = (GLchar*)malloc(blen);
		 glGetInfoLogARB(fragmentShaderObject, blen, &slen, compiler_log);
		 cout << filename  << " compiler_log " << ":\n" << compiler_log;
		 free (compiler_log);
		}
	}


	//Create a program handle.
	program = glCreateProgram();

	//Attach the shaders. Here, assume that fragmentHandle is a handle to a fragment shader object,
	//and that vertexHandle is a handle to a vertex shader object.
	glAttachShader(program, fragmentShaderObject);

	//Link the program.
	glLinkProgram(program);
}

Shader::~Shader() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
