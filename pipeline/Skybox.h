/*
 * Skybox.h
 *
 *  Created on: 13/10/2013
 *      Author: remnanjona
 */

#ifndef SKYBOX_H_
#define SKYBOX_H_

#include "../shader/Program.h"
#include "../view/ViewInterface.h"
#include "Step.h"

namespace std {

class Skybox:
		public Step
{
private:
	Program skybox;
	UniformBlock<CameraProperties> camsky;
	shared_ptr<Geometry> sky;

	/* Textures */
	Tex *cubeTex;

public:
	Skybox( VertexBuffer & );
	virtual ~Skybox();

	virtual Program &getProgram();
	virtual void update( chrono::duration<double> );
	virtual void run( shared_ptr<ViewInterface> );
};

} /* namespace std */
#endif /* SKYBOX_H_ */
