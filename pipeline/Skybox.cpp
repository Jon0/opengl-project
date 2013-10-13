/*
 * Skybox.cpp
 *
 *  Created on: 13/10/2013
 *      Author: remnanjona
 */

#include "../geometry/Cube.h"
#include "Skybox.h"

namespace std {

Skybox::Skybox( VertexBuffer &vb ):
	skybox("skybox"),
	camsky { skybox.getBlock<CameraProperties>( "Camera", 1 )},
	sky { new Cube(500) }
{
	/* sky */
	cubeTex = new Tex();
	cubeTex->make3DTex("assets/image/sky2.png");

	skybox.setUniform("cubeTexture", &cubeTex->location);

	sky->init(&vb);
}

Skybox::~Skybox() {
	// TODO Auto-generated destructor stub
}

Program &Skybox::getProgram() {
	return skybox;
}

void Skybox::update( chrono::duration<double> ) {

}

void Skybox::run( shared_ptr<ViewInterface> v ) {
	cubeTex->enable(0);

	/* TODO translate by camera position */
	glDisable(GL_CULL_FACE);
	skybox.enable();
	camsky.assign( v->properties() );
	sky->draw();
}

} /* namespace std */
