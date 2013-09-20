/*
 * Parser.h
 *
 *  Created on: 19/09/2013
 *      Author: remnanjona
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <vector>
#include <fstream>

namespace std {

template<class T> class Parser;

template<class T> struct node {

	Parser<T> next;
};

template<class T> class Parser {
public:
	vector< node<T> > opt;

	Parser() {

	}

	virtual ~Parser() {

	}

	void getLineTokens(ifstream &file) {

	}
};

} /* namespace std */
#endif /* PARSER_H_ */
