/*
 * GRender.h
 *
 *  Created on: 23/09/2013
 *      Author: remnanjona
 */

#ifndef GRENDER_H_
#define GRENDER_H_

#include <memory>
#include <vector>
#include "SceneInterface.h"
#include "../geometry/Geometry.h"
#include "../lighting/LightingModel.h"
#include "../shader/Program.h"
#include "../view/Camera.h"
#include "../view/Ortho.h"
#include "../window/MainWindow.h"

namespace std {

class GRender:
		public enable_shared_from_this<GRender>,
		public SceneInterface {
public:
	Program program;
	Program shadow;
	Program skybox;
	VertexBuffer vb;
	shared_ptr<Geometry> sky;
	shared_ptr<Geometry> sponza;
	shared_ptr<Geometry> box;
	shared_ptr<Geometry> bunny;
	shared_ptr<Geometry> sphere;
	shared_ptr<Geometry> table;
	shared_ptr<Geometry> teapot;
	shared_ptr<Geometry> torus;
	LightingModel light;

	GLuint useDiffTex, useNormTex;

	/* Textures */
	Tex *woodTex;
	Tex *woodNormTex;
	Tex *woodDispTex;

	Tex *brickTex;
	Tex *brickNormTex;

	Tex *normalTex;
	Tex *cubeTex;

	UniformBlock<CameraProperties> camsky;
	UniformBlock<CameraProperties> cam;
	UniformBlock<MaterialProperties> materialUniform;


	bool drag, showIcons;
	int selectedLight;
	int lightcontrol;
	string message;
	glm::quat click_old, click_new;
	float t;

	GRender();
	virtual ~GRender();

	void displayGeometry( UBO<CameraProperties> * );
	void drawObject( shared_ptr<Geometry>, UBO<CameraProperties> * );
	virtual void prepare();
	virtual void display( shared_ptr<ViewInterface>, chrono::duration<double> );
	virtual void displayUI();
	virtual int mouseClicked( shared_ptr<ViewInterface>, int, int, int, int );
	virtual int mouseDragged( shared_ptr<ViewInterface>, int, int );
	virtual void messageSent(string);
	virtual void keyPressed(unsigned char);
};

} /* namespace std */
#endif /* GRENDER_H_ */
