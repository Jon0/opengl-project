/*
 * Tex.cpp
 *
 *  Created on: 10/05/2013
 *      Author: remnanjona
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <png.h>
#include <jpeglib.h>
#include "../load/LineTokenizer.h"
#include "Tex.h"

#define TEXTURE_LOAD_ERROR 0

namespace std {

Tex::Tex():
		location { [](GLuint i, GLint v){ glUniform1i(i, v); } }
{
	addr = 0; //loadTexture(filename, width, height);
	type = 0;
	width = 0;
	height = 0;
}

Tex::~Tex() {
	// TODO Auto-generated destructor stub
}

void Tex::enable(GLuint i) {
	glActiveTexture(GL_TEXTURE0 + i);
	glBindTexture(type, addr);
	location.setV( i );
}

GLuint Tex::getAddr() {
	return addr;
}

void Tex::make2DTex(const string filename) {
	addr = loadGLTexture(filename);
	type = GL_TEXTURE_2D;
}

void Tex::make3DTex(const string filename) {
	GLuint textureAddr;
	glGenTextures(1, &textureAddr);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureAddr);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	TextureInfo t;
	loadTexture(filename.c_str(), &t);
	int sq = t.width / 4.0;

	// right
	unsigned char *sub = subImage(t.textureData, sq, t.width, 2, 1);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, sq, sq, 0, GL_RGB,
			GL_UNSIGNED_BYTE, sub);
	delete[] sub;

	// left
	sub = subImage(t.textureData, sq, t.width, 0, 1);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, sq, sq, 0, GL_RGB,
			GL_UNSIGNED_BYTE, sub);
	delete[] sub;

	// top
	sub = subImage(t.textureData, sq, t.width, 1, 0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, sq, sq, 0, GL_RGB,
			GL_UNSIGNED_BYTE, sub);
	delete[] sub;

	// down
	sub = subImage(t.textureData, sq, t.width, 1, 2);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, sq, sq, 0, GL_RGB,
			GL_UNSIGNED_BYTE, sub);
	delete[] sub;

	// front
	sub = subImage(t.textureData, sq, t.width, 1, 1);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, sq, sq, 0, GL_RGB,
			GL_UNSIGNED_BYTE, sub);
	delete[] sub;

	//back
	sub = subImage(t.textureData, sq, t.width, 3, 1);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, sq, sq, 0, GL_RGB,
			GL_UNSIGNED_BYTE, sub);
	delete[] sub;
	free(t.textureData);

	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	addr = textureAddr;
	width = sq;
	height = sq;
	type = GL_TEXTURE_CUBE_MAP;
}

unsigned char *Tex::subImage(unsigned char *imageData, int sq, int sizeX, int x, int y) {
	unsigned char *sub = new unsigned char[3 * sq * sq];
	for (int i = 0; i < sq; ++i)
		for (int j = 0; j < sq; ++j) {
			sub[3 * (i + j * sq) + 0] =
					imageData[3 * ((i + sq * x) + (j + sq * y) * sizeX) + 0];
			sub[3 * (i + j * sq) + 1] =
					imageData[3 * ((i + sq * x) + (j + sq * y) * sizeX) + 1];
			sub[3 * (i + j * sq) + 2] =
					imageData[3 * ((i + sq * x) + (j + sq * y) * sizeX) + 2];
		}
	return sub;
}

/** loadTexture
 *     loads a png file into an opengl texture object, using cstdio , libpng, and opengl.
 *
 *     \param filename : the png file to be loaded
 *     \param width : width of png, to be updated as a side effect of this function
 *     \param height : height of png, to be updated as a side effect of this function
 *
 *     \return GLuint : an opengl texture id.  Will be 0 if there is a major error,
 *                                     should be validated by the client of this function.
 *
 */
GLuint Tex::loadGLTexture(const string filename) {
	TextureInfo t;
	loadTexture(filename.c_str(), &t);

	//Now generate the OpenGL texture object
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t.width, t.height, 0, GL_RGB, GL_UNSIGNED_BYTE, t.textureData);
	free(t.textureData);

	// select modulate to mix texture with color for shading
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	glGenerateMipmap( GL_TEXTURE_2D );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// the texture wraps over at the edges (repeat)
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	return texture;
}

int loadTexture(const string filename, TextureInfo *t) {
	vector<string> ext = stringSplit(filename, ".");
	if (ext[1] == "jpg" || ext[1] == "jpeg" || ext[1] == "JPG" || ext[1] == "JPEG") {
		return loadTextureFromJPEG(filename, t);
	}
	else if (ext[1] == "png" || ext[1] == "PNG") {
		return loadTextureFromPNG(filename, t);
	}
	else {
		printf("Invalid format. Only supports JPEG and PNG.\n");
		return 0;
	}
}

/*
 * Magical JPEG loader. You probably shouldn't edit this.
 */
int loadTextureFromJPEG(const string filename, TextureInfo *info) {

	//Gonna need a file pointer.
	FILE *fd;

	//Init the structs required by libjpeg
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	//This will keep track of where we are in the file
	unsigned char * line;

	//Redirect stderr so things aren't messy
	cinfo.err = jpeg_std_error(&jerr);

	//Init the decompress struct
	jpeg_create_decompress(&cinfo);

	//Try to open the file. Better code would return an error value,
	//but I'm just making it exit instead.
	if (0 == (fd = fopen(filename.c_str(), "rb"))) {
		printf("Error opening file");
	}

	//Point libjpeg at the file
	jpeg_stdio_src(&cinfo, fd);
	//Read in the JPEG header
	jpeg_read_header(&cinfo, TRUE);
	//Used to keep track of offset in 1-D pixel array
	unsigned int size = cinfo.image_width;

	//Populate the texture-info struct.
	//If it's not GL_RGB, then you have a really strange JPEG.
	info->height = cinfo.image_height;
	info->width = cinfo.image_width;
	info->format = GL_RGB;
	//If your JPEG somehow has alpha, you're gonna have a bad time.
	info->hasAlpha = false;

	//Assign an array for pixels
	unsigned char* image = (unsigned char*) malloc(sizeof(char) * 3 * cinfo.image_height * cinfo.image_width);

	//Begin magic.
	jpeg_start_decompress(&cinfo);
	while (cinfo.output_scanline < cinfo.output_height) {
		line = image
				+ (3 * size) * cinfo.output_scanline;
		jpeg_read_scanlines(&cinfo, &line, 1);
	}
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	//Allocate an array for the pixels. Why two? You'll see.
	info->textureData = (unsigned char*) malloc(sizeof(char) * 3 * cinfo.image_height * cinfo.image_width);

	//Copy the pixels from image to textureData in reverse row order. Because GL.
	for(int y = info->height-1; y >= 0; y--){
		for(int x = 0; x < info->width*3; x++){
				info->textureData[(info->height-y-1)*(info->width*3)+x] = image[y*info->width*3+x];
		}
	}
	free(image);

	return 0;
}

/*
 * Magical PNG loader. You probably shouldn't edit this.
 */
int loadTextureFromPNG(const string filename, TextureInfo* t){

	//Required structs and file pointers.
	png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    FILE *fp;

    //Again, this should return an error code instead of exiting,
    //but for this assignment, it should work anyway.
    if ((fp = fopen(filename.c_str(), "rb")) == NULL){
        printf("Error opening %s\n", filename.c_str());
    }

    //Magic, do not touch.
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (png_ptr == NULL) {
    	printf("LibPNG did something terrible!\n");
        fclose(fp);
    }

    //Allocate the struct we're going to read the data into.
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
    	printf("LibPNG did something terrible!\n");
        fclose(fp);
        png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
    }

    //Error handling magic. Do not touch.
    if (setjmp(png_jmpbuf(png_ptr))) {
    	printf("LibPNG did something terrible!\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
        fclose(fp);
    }

    //Point libPNG to the right place
    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, sig_read);

    //Yet more magic you shouldn't touch. We -probably- have enough memory to read it all in one go.
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

    //Start setting values in the textureinfo struct
    //Note that PNGs -can- have alpha.
    t->width = png_get_image_width(png_ptr,info_ptr);
    t->height = png_get_image_height(png_ptr,info_ptr);
    switch (png_get_color_type(png_ptr,info_ptr)) {
        case PNG_COLOR_TYPE_RGBA:
            t->hasAlpha = true;
            break;
        case PNG_COLOR_TYPE_RGB:
        	t->hasAlpha = false;
            break;
        default:
            printf("Invalid PNG.\n");
            png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
            fclose(fp);
    }
    //How long is a row?
    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    //Allocate some space!
    t->textureData = (unsigned char*) malloc(row_bytes * t->height);

    //Read the image data into the texture array, in reverse row order. Because GL.
    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
    for (int i = 0; i < t->height; i++) {
        memcpy(t->textureData+(row_bytes * (t->height-1-i)), row_pointers[i], row_bytes);
    }

    //Clean up
    png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
    fclose(fp);

    return 0;
}

} /* namespace std */
