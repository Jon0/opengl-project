/*
 * ViewInterface.h
 *
 *  Created on: 25/08/2013
 *      Author: remnanjona
 */

#ifndef VIEWINTERFACE_H_
#define VIEWINTERFACE_H_

namespace std {

class ViewInterface {
public:
	virtual void display() = 0;
	virtual ~ViewInterface() {};
};

} /* namespace std */
#endif /* VIEWINTERFACE_H_ */
