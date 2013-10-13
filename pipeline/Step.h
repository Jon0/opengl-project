/*
 * Step.h
 *
 *  Created on: 12/10/2013
 *      Author: remnanjona
 */

#ifndef STEP_H_
#define STEP_H_

#include <memory>

#include "../scene/SceneInterface.h"
#include "../shader/Program.h"
#include "../view/ViewInterface.h"

namespace std {

/*
 * combinations of program and scene
 * scene gets updated, then program gets run
 */
class Step {
public:
	virtual ~Step() {};

	virtual Program &getProgram() = 0;
	virtual void update( chrono::duration<double> ) = 0;
	virtual void run( shared_ptr<ViewInterface> ) = 0;
};

} /* namespace std */
#endif /* STEP_H_ */
