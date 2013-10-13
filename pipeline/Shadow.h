/*
 * Shadow.h
 *
 *  Created on: 13/10/2013
 *      Author: remnanjona
 */

#ifndef SHADOW_H_
#define SHADOW_H_

#include "Step.h"

namespace std {

class Shadow:
		public Step
{
private:
	Program main;

public:
	Shadow();
	virtual ~Shadow();

	virtual Program &getProgram();
	virtual void update( chrono::duration<double> );
	virtual void run( shared_ptr<ViewInterface> );
};

} /* namespace std */
#endif /* SHADOW_H_ */
