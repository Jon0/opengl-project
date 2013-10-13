/*
 * Shadow.cpp
 *
 *  Created on: 13/10/2013
 *      Author: remnanjona
 */

#include "Shadow.h"

namespace std {

Shadow::Shadow():
		main { "light_trace" }
{
	// TODO Auto-generated constructor stub

}

Shadow::~Shadow() {
	// TODO Auto-generated destructor stub
}

Program &Shadow::getProgram() {
	return main;
}

void Shadow::update( chrono::duration<double> ) {
	main.enable();



}

void Shadow::run( shared_ptr<ViewInterface> ) {

}

} /* namespace std */
