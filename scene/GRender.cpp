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
		light { shadow, program },
		model { [](GLuint i, glm::mat4 v){ glUniformMatrix4fv(i, 1, GL_FALSE, &v[0][0]); } }
{
	mWnd->start();

	/* texturing... */
	diffuseTex = new Tex();
	diffuseTex->make2DTex("assets/image/brick.jpg");
	normalTex = new Tex();
	normalTex->make2DTex("assets/image/normal.jpg");
	cubeTex = new Tex();
	cubeTex->make3DTex("assets/image/sky2.png");

	useDiffTex = program.addUniform("useDiffTex");
	useNormTex = program.addUniform("useNormTex");

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

	/*
	 * set uniforms
	 */
	skybox.setUniform("MVP", &camera->VP);

	program.setUniform("V", &camera->view);
	program.setUniform("P", &camera->projection);
	program.setUniform("M", &model);
	program.setUniform("cubeTexture", &cubeTex->location);
	program.setUniform("diffuseTexture", &diffuseTex->location);
	program.setUniform("normalTexture", &normalTex->location);
	program.setUniform("specularTexture", &diffuseTex->location);

	skybox.setUniform("cubeTexture", &cubeTex->location);
}

/*
 * TODO only call this once
 */
void GRender::prepare() {
	shadow.enable();

	/*
	 * prepare depth map of each light
	 */
	light.getDepthMap();
	light.getShadow(table);
	light.getShadow(box);
	light.getShadow(bunny);
	light.getShadow(sphere);
	light.getShadow(teapot);
	light.getShadow(torus);
}

void GRender::display( shared_ptr<ViewInterface> cam, chrono::duration<double> ) {
	cubeTex->enable(0);

	/* TODO translate by camera position */
	glDisable(GL_CULL_FACE);
	skybox.enable();
	vb.enable();
	sky->draw();

	/*
	 * Draw the scene objects
	 */
	diffuseTex->enable(0);
	normalTex->enable(1);
	cubeTex->enable(2);

	program.enable();

	glEnable(GL_CULL_FACE);
	glUniform1i(useDiffTex, false);
	glUniform1i(useNormTex, false);

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

	model.data = glm::translate(glm::mat4(1.0f), position);
	program.enable(); // TODO hackish refresh...

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
