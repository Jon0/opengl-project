/*
 * Font.cpp
 *
 *  Created on: 3/10/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Font.h"

namespace std {

Font::Font() {
	try {
		throw 10;
	} catch (int e) {
		cerr << "errr " << e << endl;
	}


	FT_Library ft;
	if(FT_Init_FreeType(&ft)) {
	  fprintf(stderr, "Could not init freetype library\n");
	  return;
	}

	FT_Face face;
	if(FT_New_Face(ft, "/usr/local/share/fonts/Type1/Times-Roman.pfa", 0, &face)) {
	  fprintf(stderr, "Could not open font\n");
	  return;
	}
	FT_Set_Pixel_Sizes(face, 0, 48);

	if(FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
	  fprintf(stderr, "Could not load character 'X'\n");
	  return;
	}

	FT_GlyphSlot g = face->glyph;
}

Font::~Font() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
