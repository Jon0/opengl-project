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
vector<GLpolygon> GeometryLoader::readOBJ(const char *filename) {
	ifstream fs(filename);
	if (fs == NULL)
			printf("Error reading %s file\n", filename);
		else
			printf("Reading %s file\n", filename);
	fs.seekg(0, ios::beg);

	vector<GLpoint> points;
	vector<GLnormal> normals;
	vector<GLuvcoord> uvcoords;
	vector<OBJpolygon> triangles;

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
				GLuvcoord uv;
				fs >> uv.u >> uv.v;
				uvcoords.push_back(uv);
			} else if (vmode == 'n') {	// normal
				GLnormal n;
				fs >> n.x >> n.y >> n.z;
				normals.push_back(n);
			} else if (vmode == ' ') {	// vertex
				GLpoint p;
				fs >> p.x >> p.y >> p.z;
				points.push_back(p);
			}
			fs.ignore(200, '\n');
		}
		break;
		case 'f': {/* faces */
			OBJpolygon polygon{};
			vector<string> g = getLineTokens(fs);
			for (auto &vt: g) {

				/*
				 * read a vertex
				 */
				OBJvertex vertex{};
				vector<string> part = stringSplit(vt, "/");

				vertex.p = atoi(part[0].c_str()) - 1;
				if (part.size() == 2) {
					vertex.c = atoi(part[1].c_str()) - 1;
					vertex.n = -1;
				}
				else if (part.size() == 3) {
					if (part[1].length() == 0) {
						vertex.c = -1;
						vertex.n = atoi(part[2].c_str()) - 1;
					}
					else {
						vertex.c = atoi(part[1].c_str()) - 1;
						vertex.n = atoi(part[2].c_str()) - 1;
					}
				}

				polygon.push_back(vertex);
			}
			triangles.push_back(polygon);
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

	if (normals.empty()) {
		printf("Calculate Normals\n");
		normals = CreateNormals(triangles, points);
	}

	/* copy data to a usable type */
	vector<GLpolygon> polys;
	for (auto &pl: triangles) {
		GLpolygon gpl;
		for (auto &vt: pl) {
			GLvertex gvt {};
			if (vt.p >= 0) gvt.p = points.data()[vt.p];
			if (vt.c >= 0) gvt.c = uvcoords.data()[vt.c];
			if (vt.n >= 0) gvt.n = normals.data()[vt.n];
			gpl.push_back(gvt);
		}
		polys.push_back(gpl);
	}


	printf("Reading OBJ file is DONE.\n");
	return polys;
}


// TODO integrate into main parsing, since indexs are lost
vector<GLnormal> GeometryLoader::CreateNormals(vector<OBJpolygon> polys, vector<GLpoint> points) {

	/* construct array initialise to size of verts */
	vector<GLnormal> m_pNormalArray( points.size() );

	/* u will be v2 - v1, v will be v3 - v1 used in cross products */
	GLnormal u, v;
	float *uf = (float *) &u, *vf = (float *) &v;


	for (unsigned int i = 0; i < polys.size(); ++i) {
		OBJpolygon poly = polys.data()[i];

		// get address of vertices this triangle uses
		GLpoint v1 = points.data()[poly.data()[0].p];
		GLpoint v2 = points.data()[poly.data()[1].p];
		GLpoint v3 = points.data()[poly.data()[2].p];

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
















