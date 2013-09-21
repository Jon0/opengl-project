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
#include "../geometry/GVertex.h"

namespace std {

struct OBJvertex {
	int p, n, c, b;
};

typedef vector<OBJvertex> OBJpolygon;

class GeometryLoader
{
public:
	GeometryLoader(void);
	~GeometryLoader(void);

	vector<GPolygon> readOBJ(const char* filename);
	vector<Vec3D> CreateNormals(vector<OBJpolygon>, vector<Vec3D>);
	vector<Basis> CreateBasis(vector<OBJpolygon>, vector<Vec3D>, vector<Vec3D>);
};

} /* namespace std */
#endif /* GEOMETRYLOADER_H_ */


