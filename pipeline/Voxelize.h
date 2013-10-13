/*
 * Voxelize.h
 *
 *  Created on: 12/10/2013
 *      Author: remnanjona
 */

#ifndef VOXELIZE_H_
#define VOXELIZE_H_

#include "Step.h"

namespace std {

class Voxelize:
		public Step
{
private:
	Program vox;
	shared_ptr<SceneInterface> scene;

public:
	Voxelize( shared_ptr<SceneInterface> );
	virtual ~Voxelize();

	virtual Program &getProgram();
	virtual void update( chrono::duration<double> );
	virtual void run( shared_ptr<ViewInterface> );
};

} /* namespace std */
#endif /* VOXELIZE_H_ */
