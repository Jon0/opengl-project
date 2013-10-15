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

/*
 * count number of ubo's that exist, to assign unique indexes
 */
extern int ubocount;

/*
 * Wraps a struct which is used in a shader program
 */
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

	GLuint64 make_gpu_Addr() {
		GLuint64 gpuAddrs;
		// get the address of this buffer and make it resident.
		glGetBufferParameterui64vNV(GL_UNIFORM_BUFFER, GL_BUFFER_GPU_ADDRESS_NV, &gpuAddrs);
		glMakeBufferResidentNV(GL_UNIFORM_BUFFER, GL_READ_ONLY);

		return gpuAddrs;
	}


};

} /* namespace std */
#endif /* UBO_H_ */
