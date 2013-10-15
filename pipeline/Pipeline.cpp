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
		tree { new Tree(128) },
		scene { new GRender( vb ) },
		sky { new Skybox( vb ) },
		render { new Render( scene, tree ) },
		voxelize { new Voxelize( scene ) },
		lm { new LightingModel( scene ) }
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
	tree->enable( 0 );

	lm->update( tick );
	voxelize->update( tick );
}

/*
 * render scene from a given viewpoint
 */
void Pipeline::output( shared_ptr<ViewInterface> v ) {
	vb.enable();

	/*
	 * bind illumination
	 */
	tree->enable( 0 );

	lm->setLight( render->getProgram(), render->lightUniform );

	sky->run( v );
	render->run( v );

	scene->debug( v );
}

} /* namespace std */
