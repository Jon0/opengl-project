/*
 * Shader.h
 *
 *  Created on: 20/09/2013
 *      Author: remnanjona
 */

#ifndef SHADER_H_
#define SHADER_H_

namespace std {

class Shader {
public:
	GLuint ShaderHandle;
	Shader(const char *, GLenum);
	virtual ~Shader();
};

} /* namespace std */
#endif /* SHADER_H_ */
