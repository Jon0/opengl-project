/*
 * UniformBlock.h
 *
 *  Created on: 30/09/2013
 *      Author: remnanjona
 */

#ifndef UNIFORMBLOCK_H_
#define UNIFORMBLOCK_H_

#include <iostream>
#include <string>
#include <vector>
#include <GL/gl.h>

#include "UBO.h"

namespace std {

template<class T> class UniformBlock {
private:
	int length;
	string name;
	vector<UBO<T> *> blockSource;
	vector<GLuint> blockIndex;
	GLuint programID, bindingPoint;
	GLuint buffer;
	GLint blockDataSize;

public:
	UniformBlock(GLuint p, string n, int len) {
		programID = p;
		name = n;
		length = len;
		buffer = 0;
		bindingPoint = 0;

		if (length == 1) {
			blockIndex.push_back( glGetUniformBlockIndex(programID, name.c_str()) );
			//cout << blockIndex.data()[0] << ": " << name << endl;
		}
		else {
			for (int i = 0; i < length; ++i) {
				string fullname = name + "[" + to_string(i) +"]";
				blockIndex.push_back( glGetUniformBlockIndex(programID, fullname.c_str()) );
				//cout << blockIndex.data()[i] << ": " << fullname << endl;
			}
		}
		blockSource.resize(length);

		glGetActiveUniformBlockiv(programID, blockIndex.data()[0], GL_UNIFORM_BLOCK_DATA_SIZE, &blockDataSize);
		//cout << "block data size: " << blockDataSize << endl;
		//cout << "type data size: " << sizeof(T) << endl;
	}

	virtual ~UniformBlock() {}

	GLint dataSize() {
		return blockDataSize;
	}

	void assign(UBO<T> *data, int index) {
		blockSource.data()[index] = data;
		glUniformBlockBinding(programID, blockIndex[index], data->bindingPoint);
	}

	/*
	 * if its not an array of structs
	 */
	void assign(UBO<T> *data) {
		blockSource.data()[0] = data;
		glUniformBlockBinding(programID, blockIndex[0], data->bindingPoint);
	}
};

} /* namespace std */
#endif /* UNIFORMBLOCK_H_ */
