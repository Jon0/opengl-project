/*
 * Font.cpp
 *
 *  Created on: 3/10/2013
 *      Author: remnanjona
 */

#include <iostream>

#include "Font.h"

namespace std {

Font::Font() {
	try {
		throw 10;
	} catch (int e) {
		cerr << "errr " << e << endl;
	}
}

Font::~Font() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
