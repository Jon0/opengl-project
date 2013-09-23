/*
 * Tex.h
 *
 *  Created on: 10/05/2013
 *      Author: remnanjona
 */

#ifndef TEX_H_
#define TEX_H_

#include <string>
#include <png.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <jerror.h>
#include <png.h>

//Magic defines for libPNG because they removed them from the library
#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL
#define png_voidp_NULL NULL

namespace std {

/*
 *  The TextureInfo struct. This is where we keep all the texture info when we load a file.
 *  The actual image is stored as an array of unsigned characters (aka unsigned bytes).
 *  It's three bytes per pixel -- one for each color channel, so this array will have a length
 *  of width*height*3. Note that it is ONE dimensional!
 */
struct TextureInfo {
	unsigned char* textureData;
	int format;
	int width;
	int height;
	bool hasAlpha;
};

int loadTexture(const string, TextureInfo *);
int loadTextureFromJPEG(const string,TextureInfo *);
int loadTextureFromPNG(const string, TextureInfo *);

class Tex {
	GLuint addr;
	int width, height;
public:
	Tex();
	virtual ~Tex();

	GLuint getAddr();
	void make2DTex(const string filename);
	void make3DTex(const string filename);
	unsigned char *subImage(unsigned char *imageData, int, int, int, int);
	GLuint loadGLTexture(const string filename);
};

} /* namespace std */
#endif /* TEX_H_ */
