/*
 * UBO.h
 *
 *  Created on: 30/09/2013
 *      Author: remnanjona
 */

#ifndef UBO_H_
#define UBO_H_

#include <GL/gl.h>

namespace std {

extern int ubocount;

template<class T> class UBO {
private:
	GLuint buffer;

public:
	T data;
	const GLuint bindingPoint;

	UBO():
			bindingPoint(ubocount)
	{
		glGenBuffers(1, &buffer);
		ubocount++;
	}

	virtual ~UBO() {}

	void update() {
		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(T), &data, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, buffer); //bindBufferRange...
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
};

} /* namespace std */
#endif /* UBO_H_ */
