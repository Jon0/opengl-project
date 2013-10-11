/*
 * Step.h
 *
 *  Created on: 12/10/2013
 *      Author: remnanjona
 */

#ifndef STEP_H_
#define STEP_H_

namespace std {

class Step {
public:
	virtual ~Step() {};

	virtual void run() = 0;
};

} /* namespace std */
#endif /* STEP_H_ */
