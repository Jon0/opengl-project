/*
 * GRender.cpp
 *
 *  Created on: 23/09/2013
 *      Author: remnanjona
 */

#include <iostream>
#include "../geometry/Cube.h"
#include "GRender.h"

namespace std {

GRender::GRender():
		mWnd { new MainWindow(800, 600, "Scene") },
		program("phong_bump"),
		shadow("shadow_depth"),
		skybox("skybox"),
		vb(15),
		gloader(),
		sky { new Cube(500) },
		box { gloader.readOBJG("assets/obj/Box.obj") },
		bunny { gloader.readOBJG("assets/obj/Bunny.obj") },
		sphere { gloader.readOBJG("assets/obj/Sphere.obj") },
		table { gloader.readOBJG("assets/obj/Table.obj") },
		teapot { gloader.readOBJG("assets/obj/Teapot.obj") },
		torus { gloader.readOBJG("assets/obj/Torus.obj") },
		light { shadow, program }
{
	mWnd->start();

	/*
	 * set uniforms
	 */
	ModelView3x3MatrixID = program.addUniform("MV3x3");
	MatrixID = program.addUniform("MVP");
	ViewMatrixID = program.addUniform("V");
	ModelMatrixID = program.addUniform("M");

	CubeTextureID = program.addUniform("cubeTexture");
	DiffuseTextureID = program.addUniform("diffuseTexture");
	NormalTextureID = program.addUniform("normalTexture");
	SpecularTextureID = program.addUniform("specularTexture");
	useDiffTex = program.addUniform("useDiffTex");
	useNormTex = program.addUniform("useNormTex");

	SkyCubeTextureID = skybox.addUniform("cubeTexture");
	SkyMatrixID = skybox.addUniform("MVP");

	/* texturing... */
	diffuseTex = new Tex();
	diffuseTex->make2DTex("assets/image/brick.jpg");
	normalTex = new Tex();
	normalTex->make2DTex("assets/image/normal.jpg");
	cubeTex = new Tex();
	cubeTex->make3DTex("assets/image/sky2.png");

	// setup VBO
	sky->init(&vb);
	box->init(&vb);
	bunny->init(&vb);
	sphere->init(&vb);
	table->init(&vb);
	teapot->init(&vb);
	torus->init(&vb);
	vb.store();

	table->setTransform( glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0)) );
	box->setTransform( glm::translate(glm::mat4(1.0), glm::vec3(3.0, 2.5, 4.0)) );
	bunny->setTransform( glm::translate(glm::mat4(1.0), glm::vec3(4,0.6,-5)) );
	sphere->setTransform( glm::translate(glm::mat4(1.0), glm::vec3(7,1.8,2)) );
	teapot->setTransform( glm::translate(glm::mat4(1.0), glm::vec3(-3,0.6,-5)) );
	torus->setTransform( glm::translate(glm::mat4(1.0), glm::vec3(-5,1,5)) );

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

GRender::~GRender() {
	// TODO Auto-generated destructor stub
}

void GRender::start() {
	camera = shared_ptr<Camera>{ new Camera( shared_from_this(), mWnd ) };
	mWnd->addView( camera );
}

/*
 * TODO only call this once
 */
void GRender::prepare() {
	shadow.enable();

	// TODO translatable interface
	light.getDepthMap();
	light.getShadow(table);
	light.getShadow(box);
	light.getShadow(bunny);
	light.getShadow(sphere);
	light.getShadow(teapot);
	light.getShadow(torus);
}

void GRender::display( shared_ptr<ViewInterface>, chrono::duration<double> ) {
	skybox.enable(); // must be first

	// TODO get this from camera
	GLfloat modelview[16];
	GLfloat projection[16];
	glGetFloatv( GL_MODELVIEW_MATRIX, modelview );
	glGetFloatv( GL_PROJECTION_MATRIX, projection );

	ProjectionMatrix = glm::make_mat4(projection);
	ViewMatrix = glm::make_mat4(modelview);
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix;
	glUniformMatrix4fv(SkyMatrixID, 1, GL_FALSE, &MVP[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTex->getAddr());
	glUniform1i(SkyCubeTextureID, 0);

	/* TODO translate by camera position */
	glDisable(GL_CULL_FACE);
	vb.enable();
	sky->draw();

	/*
	 * Draw the scene objects
	 */
	program.enable(); // must be first

	// Bind our diffuse texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTex->getAddr());
	glUniform1i(DiffuseTextureID, 0);
	glUniform1i(SpecularTextureID, 0);
	glUniform1i(useDiffTex, false);

	// Bind our normal texture in Texture Unit 1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normalTex->getAddr());
	glUniform1i(NormalTextureID, 1);
	glUniform1i(useNormTex, false);

	//glEnable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTex->getAddr());
	glUniform1i(CubeTextureID, 2);

	// setup bump mapping
	// TODO get this from camera
	//GLfloat modelview[16];
	//GLfloat projection[16];
	//glGetFloatv( GL_MODELVIEW_MATRIX, modelview );
	//glGetFloatv( GL_PROJECTION_MATRIX, projection );
	//ProjectionMatrix = glm::make_mat4(projection);
	//ViewMatrix = glm::make_mat4(modelview);

	light.setLight();
	displayGeometry();
}

void GRender::displayGeometry() {
	vb.enable();

	setTranslation(glm::vec3(0,0,0));
	table->draw();

	setTranslation(glm::vec3(3,2.5,4));
	box->draw();

	setTranslation(glm::vec3(4,0.6,-5));
	bunny->draw();

	setTranslation(glm::vec3(7,1.8,2));
	sphere->draw();

	setTranslation(glm::vec3(-3,0.6,-5));
	teapot->draw();

	setTranslation(glm::vec3(-5,1,5));
	torus->draw();
}

void GRender::setTranslation(glm::vec3 position) {
	light.setTranslation(position);
	light.setTranslationB();

	ModelMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
	glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix); // Take the upper-left part of ModelViewMatrix
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix3fv(ModelView3x3MatrixID, 1, GL_FALSE, &ModelView3x3Matrix[0][0]);
}

int GRender::mouseClicked( shared_ptr<ViewInterface>, int, int, int, int ) {
	return false;
}

int GRender::mouseDragged( shared_ptr<ViewInterface>, int, int ) {
	return false;
}

void GRender::messageSent(string) {

}

void GRender::keyPressed(unsigned char) {

}

} /* namespace std */
