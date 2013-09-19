/*
 * LineTokenizer.h
 *
 *  Created on: Apr 9, 2013
 *      Author: remnanjona
 */

#ifndef LINETOKENIZER_H_
#define LINETOKENIZER_H_

#include <iostream>
#include <fstream>
#include <vector>

namespace std {

/**
 * reads a line ending with \n, seperatings the contents into tokens
 * result is returned as a vector of strings
 */
vector<string> getLineTokens(ifstream &file);

vector<string> stringSplit(string s, string delimiter);


} /* namespace std */
#endif /* LINETOKENIZER_H_ */
