/*
 * Render.h
 *
 *  Created on: 13/10/2013
 *      Author: remnanjona
 */

#ifndef RENDER_H_
#define RENDER_H_

#include <memory>

#include "../octree/Tree.h"
#include "../pipeline/Step.h"
#include "../scene/SceneInterface.h"
#include "../shader/Program.h"
#include "../shader/ShaderStructs.h"

namespace std {

class Render:
		public Step
{
private:
	Program main;
	shared_ptr<SceneInterface> scene;
	shared_ptr<Tree> tree;
	GLuint useDiffTex, useNormTex;

public:
	UniformBlock<CameraProperties> cam;
	UniformBlock<MaterialProperties> materialUniform;
	UniformBlock<LightProperties> lightUniform;
	UniformControl<GLint> diffuse_tex, specular_tex;
	//UniformBlock<OctreeNode> node;

	Render( shared_ptr<SceneInterface>, shared_ptr<Tree>  );
	virtual ~Render();

	virtual Program &getProgram();
	virtual void update( chrono::duration<double> );
	virtual void run( shared_ptr<ViewInterface> );
};

} /* namespace std */
#endif /* RENDER_H_ */
