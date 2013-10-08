/*
 * GeometryLoader.cpp
 *
 *  Created on: 1/09/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>

#include "GeometryLoader.h"

namespace std {

void copyVec3(glm::vec3 &out, const aiVector3D &in) {
	out.x = in.x;
	out.y = in.y;
	out.z = in.z;
}

vector<GPolygon> readOBJFile(const char* filename) {

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename,
			aiProcess_CalcTangentSpace | aiProcess_Triangulate
					| aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);


	cout << filename << " contains " << scene->mNumMeshes << " meshes" << endl;


	/* array of all polygons */
	vector<GPolygon> g_polys;

	/* add each polygon */
	for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
		aiMesh &mesh = *scene->mMeshes[m];
		//cout << "num faces = " << mesh.mNumFaces << endl;
		//cout << "has tangents = " << mesh.HasTangentsAndBitangents() << endl;

		for (unsigned int i = 0; i < mesh.mNumFaces; ++i) {
			GPolygon plg;

			for (unsigned int j = 0; j < mesh.mFaces[i].mNumIndices; ++j) {
				unsigned int ind = mesh.mFaces[i].mIndices[j];
				GVertex vrt;
				copyVec3(vrt.position, mesh.mVertices[ind]);
				vrt.position *= 10;

				copyVec3(vrt.normal, mesh.mNormals[ind]);

				/* tex coord if available */
				if (mesh.mNumUVComponents[0]) {
					aiVector3D &c = mesh.mTextureCoords[0][ind];
					vrt.texCoord.x = c.x;
					vrt.texCoord.y = c.y;
				}

				/* tangent and bitangent if available */
				if (mesh.HasTangentsAndBitangents()) {
					copyVec3(vrt.tangent, mesh.mTangents[ind]);
					copyVec3(vrt.bitangent, mesh.mBitangents[ind]);
					vrt.tangent = -vrt.tangent; // this seems to fix something
				}
				plg.push_back(vrt);
			}

			g_polys.push_back(plg);
		}
	}
	return g_polys;
}

shared_ptr<Geometry> readGeometry(const char* filename) {
	return shared_ptr<Geometry>(new DrawList(readOBJFile(filename)));
}

}
