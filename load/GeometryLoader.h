/*
 * GeometryLoader.h
 *
 *  Created on: 1/09/2013
 *      Author: remnanjona
 */

#ifndef GEOMETRYLOADER_H_
#define GEOMETRYLOADER_H_

#include <memory>
#include <vector>
#include <fstream>
#include <GL/glut.h>
#include "../geometry/DrawList.h"
#include "../geometry/Geometry.h"
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

	shared_ptr<Geometry> readOBJG( const char* filename );
	vector<GPolygon> readOBJ( const char* filename );
	vector<Vec3D> CreateNormals( vector<OBJpolygon>, vector<Vec3D> );
	void CreateUV( vector<GPolygon> &, int, vector<vector<int>> );
	void CreateBasis( vector<GPolygon> &, int, vector<vector<int>> );
};

} /* namespace std */
#endif /* GEOMETRYLOADER_H_ */


