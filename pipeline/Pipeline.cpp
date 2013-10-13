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
		render { new Render( scene ) },
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

void Pipeline::update( chrono::duration<double> tick ) {
	scene->update( tick );
	lm->update( tick );
	voxelize->update( tick );
}

void Pipeline::output( shared_ptr<ViewInterface> v ) {
	vb.enable();

	lm->setLight( render->getProgram(), render->lightUniform );

	sky->run( v );
	lm->run( v );
	render->run( v );

	scene->debug( v );
}

} /* namespace std */
