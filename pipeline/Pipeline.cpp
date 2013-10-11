/*
 * Pipeline.cpp
 *
 *  Created on: 12/10/2013
 *      Author: remnanjona
 */

#include "Pipeline.h"

namespace std {

Pipeline::Pipeline():
		program("phong_bump"),
		skybox("skybox"),
		light {program},
		camsky { skybox.getBlock<CameraProperties>( "Camera", 1 ) },
		cam { program.getBlock<CameraProperties>( "Camera", 1 ) },
		materialUniform { program.getBlock<MaterialProperties>("MaterialProperties", 1) }
{

}

Pipeline::~Pipeline() {
	// TODO Auto-generated destructor stub
}

void Pipeline::run( shared_ptr<SceneInterface> s ) {
}

} /* namespace std */
