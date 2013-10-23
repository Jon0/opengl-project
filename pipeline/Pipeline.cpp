/*
 * Pipeline.cpp
 *
 *  Created on: 12/10/2013
 *      Author: remnanjona
 */

#include "../scene/GRender.h"
#include "Pipeline.h"

namespace std {

Pipeline::Pipeline():
		vb { 15 },
		scene { new GRender( vb ) },
		sky { new Skybox( vb ) },
		tree { new Tree(128, scene) },
		render { new Render( scene, tree ) },
		voxelize { new Voxelize( scene ) },
		lm { new LightingModel( scene, tree ) }
{
	scene->setLightModel( lm.get() );

	steps.push_back( sky );
	steps.push_back( lm );
	steps.push_back( render );

	/* finalise vb */
	vb.store();
}

Pipeline::~Pipeline() {
	// TODO Auto-generated destructor stub
}

/*
 * process scene information that is not camera specific
 */
void Pipeline::update( chrono::duration<double> tick ) {
	scene->update( tick );


	/*
	 * gather light into tree
	 */
	//shadow->update( tick );

	/*
	 * fill image with lighting information
	 */
	lm->update( tick );
	lm->insertLight(tree);
}

/*
 * render scene from a given viewpoint
 */
void Pipeline::output( shared_ptr<ViewInterface> v ) {
	vb.enable();

	/*
	 * bind illumination
	 */
	//tree->enable( 0 );
	tree->enableTex( render->getProgram(), 2 );
	render->GI = scene->useGI;

	lm->setLight( render->getProgram(), render->lightUniform );


	sky->run( v );
	render->run( v );

	scene->debug( v );
}

} /* namespace std */
