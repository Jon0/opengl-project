/*
 * GeometryLoader.cpp
 *
 *  Created on: 1/09/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "LineTokenizer.h"
#include "GeometryLoader.h"

using namespace std;

GeometryLoader::GeometryLoader() {}

GeometryLoader::~GeometryLoader() {}

//-------------------------------------------------------
// This function read obj file having
// triangle faces consist of vertex v, texture coordinate vt, and normal vn
// e.g. f v1/vt1/vn1 v2/vt1/vn2 v3/vt3/vn3
//--------------------------------------------------------
vector<GPolygon> GeometryLoader::readOBJ(const char *filename) {
	ifstream fs(filename);
	if (fs == NULL)
			printf("Error reading %s file\n", filename);
		else
			printf("Reading %s file\n", filename);
	fs.seekg(0, ios::beg);

	vector<Vec3D> points;
	vector<Vec3D> normals;
	vector<Vec3D> uvcoords;
	vector<GPolygon> g_polys;

	// polygon -> number -> array position
	vector<vector<int>> index;

	//-----------------------------------------------------------
	//	Read obj file
	//-----------------------------------------------------------
	char mode, vmode;
	while ( fs.good() ) {
		fs.get(mode);
		switch (mode) {
		case 'v': {	/* vertex, uv, normal */
			fs.get(vmode);
			if (vmode == 't') {			// uv coordinate
				Vec3D uv;
				fs >> uv.v[0] >> uv.v[1];
				uvcoords.push_back(uv);
			} else if (vmode == 'n') {	// normal
				Vec3D n;
				fs >> n.v[0] >> n.v[1] >> n.v[2];
				normals.push_back(n);
			} else if (vmode == ' ') {	// vertex
				Vec3D p;
				fs >> p.v[0] >> p.v[1] >> p.v[2];
				points.push_back(p);
			}
			fs.ignore(200, '\n');
		}
		break;
		case 'f': {	/* faces */
			GPolygon plg;
			vector<int> sub_index;
			vector<string> g = getLineTokens(fs);
			for (auto &vt: g) {

				/*
				 * read a vertex
				 */
				GVertex vrt;
				vector<string> part = stringSplit(vt, "/");

				int index = atoi(part[0].c_str()) - 1;
				vrt.e[POS] = points.data()[index];

				if (part.size() == 2) {
					vrt.e[UV] = uvcoords.data()[ atoi(part[1].c_str()) - 1 ];
				}
				else if (part.size() == 3) {
					if (part[1].length() == 0) {
						vrt.e[NORM] = normals.data()[ atoi(part[2].c_str()) - 1 ];
					}
					else {
						vrt.e[UV] = uvcoords.data()[ atoi(part[1].c_str()) - 1 ];
						vrt.e[NORM] = normals.data()[ atoi(part[2].c_str()) - 1 ];
					}
				}
				plg.push_back(vrt);
				sub_index.push_back(index);
			}

			/*
			 * avoid adding silly polygons
			 */
			if (plg.size() > 2) {
				g_polys.push_back(plg);
				index.push_back( sub_index );
			}
		}
		break;
		default:
			fs.ignore(200, '\n');
			break;
		}
	}

	/*
	 * close file
	 */
	fs.close();
	//if (normals.empty()) {
	//	printf("Calculate Normals\n");
	//	normals = CreateNormals(triangles, points);
	//}

	if (uvcoords.size() > 0) CreateBasis(g_polys, points.size(), index);


	printf("Reading OBJ file is DONE.\n");
	return g_polys;
}


// TODO integrate into main parsing, since indexs are lost
vector<Vec3D> GeometryLoader::CreateNormals(vector<OBJpolygon> polys, vector<Vec3D> points) {

	/* construct array initialise to size of verts */
	vector<Vec3D> m_pNormalArray( points.size() );

	/* u will be v2 - v1, v will be v3 - v1 used in cross products */
	Vec3D u, v;
	float *uf = (float *) &u, *vf = (float *) &v;


	for (unsigned int i = 0; i < polys.size(); ++i) {
		OBJpolygon poly = polys.data()[i];

		// get address of vertices this triangle uses
		Vec3D v1 = points.data()[poly.data()[0].p];
		Vec3D v2 = points.data()[poly.data()[1].p];
		Vec3D v3 = points.data()[poly.data()[2].p];

		// u = v2 - v1 and v = v3 - v1
		for (int a = 0; a < 3; ++a) {
			uf[a] = ((float *)&v2)[a] - ((float *)&v1)[a];
			vf[a] = ((float *)&v3)[a] - ((float *)&v1)[a];
			poly.data()[a].n = poly.data()[a].c; // each vertex has a unique normal
		}

		// cross product
		float cross[3];

		// v iterates over directions x, y, z
		for (int v = 0; v < 3; ++v) {
			cross[v] = ( uf[(v+1) % 3] * vf[(v+2) % 3] ) - ( uf[(v+2) % 3] * vf[(v+1) % 3] );
		}

		// length of normal vector
		float d = sqrt(cross[0]*cross[0] + cross[1]*cross[1] + cross[2]*cross[2]);

		for (int v = 0; v < 3; ++v) {
			//	normalising
			cross[v] /= d;

			// added to each normal
			for (int a = 0; a < 3; ++a) {
				((float *)&m_pNormalArray.data()[poly.data()[a].n])[v] += cross[v];
			}
		}
	}
	return m_pNormalArray;
}

void GeometryLoader::CreateBasis(vector<GPolygon> polys, int size, vector<vector<int>> index) {

	/* one basis per vertex */
	vector<Basis> basisArray( size );

	basisArray.data()[0].print();

	for (unsigned int i = 0; i < polys.size(); ++i) {
		GPolygon poly = polys.data()[i];

		// get address of vertices this triangle uses
		GVertex v1 = poly.data()[0];
		GVertex v2 = poly.data()[1];
		GVertex v3 = poly.data()[2];

		Basis b = textureBasis(&v1, &v2, &v3);

		b.print();


		for ( int &k: index.data()[i] ) {
			basisArray.data()[k] += b;
		}
	}

	// then normalise all basis
	for ( Basis basis: basisArray ) {
		basis.normalise();
	}

	// final assignment of basis
	for (unsigned int i = 0; i < polys.size(); ++i) {
		GPolygon poly = polys.data()[i];
		for (unsigned int j = 0; j < poly.size(); ++j) {
			int offset = index.data()[i].data()[j];
			poly.data()[j].basis = basisArray.data()[offset];
		}
	}

}
















