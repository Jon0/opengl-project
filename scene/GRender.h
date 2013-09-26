/*
 * GRender.h
 *
 *  Created on: 23/09/2013
 *      Author: remnanjona
 */

#ifndef GRENDER_H_
#define GRENDER_H_

#include <memory>
#include "SceneInterface.h"
#include "../geometry/Geometry.h"
#include "../lighting/Light.h"
#include "../load/GeometryLoader.h"
#include "../shader/Program.h"
#include "../view/Camera.h"
#include "../window/MainWindow.h"

namespace std {

class GRender:
		public enable_shared_from_this<GRender>,
		public SceneInterface {
public:
	shared_ptr<MainWindow> mWnd;
	Program program;
	Program shadow;
	Program skybox;
	VertexBuffer vb;
	GeometryLoader gloader;
	shared_ptr<Camera> camera;
	shared_ptr<Geometry> sky;
	shared_ptr<Geometry> box;
	shared_ptr<Geometry> bunny;
	shared_ptr<Geometry> sphere;
	shared_ptr<Geometry> table;
	shared_ptr<Geometry> teapot;
	shared_ptr<Geometry> torus;


	Light light;

	/*
	 * uniforms
	 */
	GLuint ModelView3x3MatrixID;
    GLuint MatrixID;
    GLuint ViewMatrixID;
    GLuint ModelMatrixID;

    GLuint CubeTextureID;
	GLuint DiffuseTextureID;
	GLuint NormalTextureID;
	GLuint SpecularTextureID;
	GLuint useDiffTex, useNormTex;

	/*
	 * skybox uniforms
	 */
	GLuint SkyCubeTextureID;
	GLuint SkyMatrixID;
	GLuint SkyViewMatrixID;

	/* matrix */
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;

	/* Textures */
	Tex *diffuseTex;
	Tex *normalTex;
	Tex *cubeTex;



	GRender();
	virtual ~GRender();

	void start();
	void setTranslation(glm::vec3 position);
	virtual void prepare();
	virtual void display( shared_ptr<ViewInterface>, chrono::duration<double> );
	virtual void displayGeometry();
	virtual int mouseClicked( shared_ptr<ViewInterface>, int, int, int, int );
	virtual int mouseDragged( shared_ptr<ViewInterface>, int, int );
	virtual void messageSent(string);
	virtual void keyPressed(unsigned char);
};

} /* namespace std */
#endif /* GRENDER_H_ */
