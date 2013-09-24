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
	else {
		cout << "file not found" << endl;
	}
	fragmentShaderFile.close();

	ShaderHandle = glCreateShader(type);
	const char *g = fragmentShaderSource.c_str();

	cout << g << endl;
	glShaderSource(ShaderHandle, 1, &g, NULL);
	glCompileShader(ShaderHandle);

	//Error checking.
	int isCompiled;
	glGetShaderiv(ShaderHandle, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
	        GLint maxLength = 0;
	        glGetShaderiv(ShaderHandle, GL_INFO_LOG_LENGTH, &maxLength);

	        //The maxLength includes the NULL character
	        std::vector<char> errorLog(maxLength);
	        glGetShaderInfoLog(ShaderHandle, maxLength, &maxLength, &errorLog[0]);

	        //Provide the infolog in whatever manor you deem best.
	        //Exit with failure.
	        glDeleteShader(ShaderHandle); //Don't leak the shader.
	        return;
	}
}

Shader::~Shader() {
	glDeleteShader(ShaderHandle);
}

} /* namespace std */
