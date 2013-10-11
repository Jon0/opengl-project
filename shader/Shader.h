/*
 * Shader.h
 *
 *  Created on: 20/09/2013
 *      Author: remnanjona
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <GL/gl.h>

namespace std {

class Shader {
public:
	GLuint ShaderHandle;
	Shader();
	Shader(string, GLenum);
	virtual ~Shader();
};

} /* namespace std */
#endif /* SHADER_H_ */
