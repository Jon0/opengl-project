/*
 * LineTokenizer.cpp
 *
 *  Created on: Apr 9, 2013
 *      Author: remnanjona
 */

#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "LineTokenizer.h"

namespace std {

/**
 * reads a line ending with \n, seperatings the contents into tokens
 * result is returned as a vector of strings
 */
vector<string> getLineTokens(ifstream &file) {
	string line;
	getline(file, line);
	istringstream iss(line);
	vector<string> tokens;
	copy(istream_iterator<string>(iss), istream_iterator<string>(),
			back_inserter<vector<string>>(tokens));
	return tokens;
}

vector<string> stringSplit(string s, string delimiter) {
	size_t pos = 0;
	vector<string> tokens;
	string token;
	while ((pos = s.find(delimiter)) != string::npos) {
		tokens.push_back( s.substr(0, pos) );
	    s.erase(0, pos + delimiter.length());
	}
	tokens.push_back( s );
	return tokens;
}

} /* namespace std */
