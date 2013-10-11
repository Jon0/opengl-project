/*
 * Pipeline.h
 *
 *  Created on: 12/10/2013
 *      Author: remnanjona
 */

#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <memory>

#include "../lighting/LightingModel.h"
#include "../shader/Program.h"
#include "../shader/UniformBlock.h"
#include "../scene/SceneInterface.h"

namespace std {

class Pipeline {
private:
	Program program;
	Program skybox;
	LightingModel light;
	UniformBlock<CameraProperties> camsky;
	UniformBlock<CameraProperties> cam;
	UniformBlock<MaterialProperties> materialUniform;

public:
	Pipeline();
	virtual ~Pipeline();

	void run( shared_ptr<SceneInterface> );
};

} /* namespace std */
#endif /* PIPELINE_H_ */
