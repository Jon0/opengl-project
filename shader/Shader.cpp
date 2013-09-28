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

Shader::Shader(string filename, GLenum type) {
	// load the fragment shader.
	fstream fragmentShaderFile(filename, std::ios::in);
	string fragmentShaderSource;
	if (fragmentShaderFile.is_open()) {
		stringstream buffer;
		buffer << fragmentShaderFile.rdbuf();
		fragmentShaderSource = buffer.str();
	}
	else {
		cerr << "file not found" << endl;
	}
	fragmentShaderFile.close();

	ShaderHandle = glCreateShader(type);
	const char *g = fragmentShaderSource.c_str();
	glShaderSource(ShaderHandle, 1, &g, NULL);
	glCompileShader(ShaderHandle);

	//Error checking.
	int isCompiled;
	glGetShaderiv(ShaderHandle, GL_COMPILE_STATUS, &isCompiled);
	if( !isCompiled )
	{
	        GLint maxLength = 0;
	        glGetShaderiv(ShaderHandle, GL_INFO_LOG_LENGTH, &maxLength);

	        //The maxLength includes the NULL character
	        std::vector<char> errorLog(maxLength);
	        glGetShaderInfoLog(ShaderHandle, maxLength, &maxLength, errorLog.data()); // &errorLog[0]
	        cerr << "error in file " << filename << endl;
	        cerr << errorLog.data() << endl;

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
