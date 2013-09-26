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
		vb(15),
		gloader(),
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

	DiffuseTextureID = program.addUniform("diffuseTexture");
	NormalTextureID = program.addUniform("normalTexture");
	SpecularTextureID = program.addUniform("specularTexture");
	useDiffTex = program.addUniform("useDiffTex");
	useNormTex = program.addUniform("useNormTex");

	/* texturing... */
	diffuseTex = new Tex();
	diffuseTex->make2DTex("assets/image/brick.jpg");
	normalTex = new Tex();
	normalTex->make2DTex("assets/image/normal.jpg");

	// setup VBO
	box->init(&vb);
	bunny->init(&vb);
	sphere->init(&vb);
	table->init(&vb);
	teapot->init(&vb);
	torus->init(&vb);
	vb.store();
}

GRender::~GRender() {
	// TODO Auto-generated destructor stub
}

void GRender::start() {
	camera = shared_ptr<Camera>{ new Camera( shared_from_this(), mWnd ) };
	mWnd->addView( camera );
}

void GRender::prepare() {
	shadow.enable();

	// TODO translatable interface
	light.getDepthMap();

	light.setTranslation(glm::vec3(0,0,0));
	table->draw();

	light.setTranslation(glm::vec3(3,2.5,4));
	box->draw();

	light.setTranslation(glm::vec3(4,0.75,-5));
	bunny->draw();

	light.setTranslation(glm::vec3(7,1.5,2));
	sphere->draw();

	light.setTranslation(glm::vec3(-3,0.75,-5));
	teapot->draw();

	light.setTranslation(glm::vec3(-5,1,5));
	torus->draw();
}

void GRender::display( shared_ptr<ViewInterface>, chrono::duration<double> ) {
	program.enable(); // must be first

	// Bind our diffuse texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTex->getAddr());
	glUniform1i(DiffuseTextureID, 0);
	glUniform1i(SpecularTextureID, 0);
	glUniform1i(useDiffTex, true);

	// Bind our normal texture in Texture Unit 1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normalTex->getAddr());
	glUniform1i(NormalTextureID, 1);
	glUniform1i(useNormTex, true);

	// setup bump mapping
	// TODO get this from camera
	GLfloat modelview[16];
	GLfloat projection[16];
	glGetFloatv( GL_MODELVIEW_MATRIX, modelview );
	glGetFloatv( GL_PROJECTION_MATRIX, projection );

	ProjectionMatrix = glm::make_mat4(projection);
	ViewMatrix = glm::make_mat4(modelview);

	light.setLight();
	displayGeometry();
}

void GRender::displayGeometry() {
	vb.enable();

	setTranslation(glm::vec3(0,0,0));
	table->draw();

	setTranslation(glm::vec3(3,2.5,4));
	box->draw();

	setTranslation(glm::vec3(4,0.75,-5));
	bunny->draw();

	setTranslation(glm::vec3(7,1.5,2));
	sphere->draw();

	setTranslation(glm::vec3(-3,0.75,-5));
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
