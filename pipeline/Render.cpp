/*
 * Render.cpp
 *
 *  Created on: 13/10/2013
 *      Author: remnanjona
 */

#include "Render.h"

namespace std {

Render::Render( shared_ptr<SceneInterface> s, shared_ptr<Tree> t ):
		main { "phong_bump" },
		scene { s },
		tree { t },
		cam { main.getBlock<CameraProperties>( "Camera", 1 ) },
		materialUniform { main.getBlock<MaterialProperties>("MaterialProperties", 1) },
		lightUniform { main.getBlock<LightProperties>("LightProperties", 8) },
		diffuse_tex { [](GLuint i, GLint v){ glUniform1i(i, v); } },
		specular_tex { [](GLuint i, GLint v){ glUniform1i(i, v); } },
		weight_tex { [](GLuint i, GLint v){ glUniform1i(i, v); } }
		//node { main.getBlock<OctreeNode>("OctreeNode", 1) }
{
	/*
	 * set uniforms
	 */
	useDiffTex = main.addUniform("useDiffTex");
	useNormTex = main.addUniform("useNormTex");
	useWeights = main.addUniform("useWeights");

	main.setUniform("diffuseTexture", &diffuse_tex);
	main.setUniform("specularTexture", &specular_tex);

	GLuint treeUniform = main.addUniform("tree");
	glUniformui64NV(treeUniform, tree->root.gpuAddr);
}

Render::~Render() {
	// TODO Auto-generated destructor stub
}

Program &Render::getProgram() {
	return main;
}

void Render::update( chrono::duration<double> ) {

}

void Render::run( shared_ptr<ViewInterface> c ) {
	/*
	 * Draw the scene objects
	 */
	//cubeTex->enable(3);

	main.enable();

	//node.assign( &tree->root );
	cam.assign( c->properties() );
	UBO<CameraProperties> *camptr = c->properties();

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUniform1i(useDiffTex, true);
	diffuse_tex.setV( 1 );
	specular_tex.setV( 1 );

	for ( auto &g: scene->content() ) {

		materialUniform.assign( g->materialUBO() );

		//light.setTransform(g->transform());
		camptr->data.M = g->transform();
		camptr->update();

		g->draw();
	}

}

} /* namespace std */
