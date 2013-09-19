/*
 * GeometryLoader.h
 *
 *  Created on: 1/09/2013
 *      Author: remnanjona
 */

#ifndef GEOMETRYLOADER_H_
#define GEOMETRYLOADER_H_

#include <vector>
#include <fstream>
#include <GL/glut.h>

namespace std {

struct GLpoint {
	float x;
	float y;
	float z;
};

typedef GLpoint GLnormal;

struct GLuvcoord {
	float u;
	float v;
};

struct GLvertex {
	GLpoint p;
	GLnormal n;
	GLuvcoord c;
};

typedef vector<GLvertex> GLpolygon;

struct OBJvertex {
	int p, n, c;
};

typedef vector<OBJvertex> OBJpolygon;

class G308_Geometry
{
public:
	G308_Geometry(void);
	~G308_Geometry(void);

	vector<GLpolygon> readOBJ(const char* filename);
	vector<GLnormal> CreateNormals(vector<OBJpolygon>, vector<GLpoint>);
};

} /* namespace std */
#endif /* GEOMETRYLOADER_H_ */


