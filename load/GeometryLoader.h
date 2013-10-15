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
#include "../geometry/DrawList.h"
#include "../geometry/Geometry.h"
#include "../geometry/GVertex.h"
#include "../geometry/GMesh.h"

namespace std {

vector<GMesh> readOBJFile( const char* );
shared_ptr<DrawList> readGeometry( const char* );

} /* namespace std */
#endif /* GEOMETRYLOADER_H_ */


