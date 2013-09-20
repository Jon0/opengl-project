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
#include "../geometry/Drawable.h"

namespace std {

struct OBJvertex {
	int p, n, c;
};

typedef vector<OBJvertex> OBJpolygon;

class GeometryLoader
{
public:
	GeometryLoader(void);
	~GeometryLoader(void);

	vector<GLpolygon> readOBJ(const char* filename);
	vector<GLnormal> CreateNormals(vector<OBJpolygon>, vector<GLpoint>);
};

} /* namespace std */
#endif /* GEOMETRYLOADER_H_ */


