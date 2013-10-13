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
#include "../octree/Tree.h"
#include "../scene/GRender.h"
#include "../shader/Program.h"
#include "../shader/UniformBlock.h"
#include "Render.h"
#include "Shadow.h"
#include "Skybox.h"
#include "Step.h"
#include "Voxelize.h"

namespace std {

class Pipeline {
public:
	VertexBuffer vb;
	vector< shared_ptr<Step> > steps;
	shared_ptr<GRender> scene;
	shared_ptr<Skybox> sky;
	shared_ptr<Render> render;
	shared_ptr<Shadow> shadow;
	shared_ptr<Voxelize> voxelize;
	shared_ptr<LightingModel> lm;

	/*
	 * Global illumination octree
	 */
	Tree tree;

	Pipeline();
	virtual ~Pipeline();

	void update( chrono::duration<double> );
	void output( shared_ptr<ViewInterface> );
};

} /* namespace std */
#endif /* PIPELINE_H_ */
