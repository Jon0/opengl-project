/*
 * GRender.cpp
 *
 *  Created on: 23/09/2013
 *      Author: remnanjona
 */

#include <iostream>
#include "../geometry/Cube.h"
#include "../texture/Font.h"
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

	new Font();

	/* texturing... */
	woodTex = new Tex();
	woodTex->make2DTex("assets/image/Burled Cherry_DIFFUSE.jpg");
	woodNormTex = new Tex();
	woodNormTex->make2DTex("assets/image/Burled Cherry_NORMAL.jpg");
	woodDispTex = new Tex();
	woodDispTex->make2DTex("assets/image/Burled Cherry_DISP.jpg");

	brickTex = new Tex();
	brickTex->make2DTex("assets/image/brickdiff.jpg");
	brickNormTex = new Tex();
	brickNormTex->make2DTex("assets/image/bricknorm.jpg");

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
	box->setTransform( glm::translate(glm::mat4(1.0), glm::vec3(5.0, 2.5, 6.0)) );
	bunny->setTransform( glm::translate(glm::mat4(1.0), glm::vec3(0,0.5,0)) );
	sphere->setTransform( glm::translate(glm::mat4(1.0), glm::vec3(4,2.0,-7)) );
	teapot->setTransform( glm::translate(glm::mat4(1.0), glm::vec3(-4,0.5,-7)) );
	torus->setTransform( glm::translate(glm::mat4(1.0), glm::vec3(-6,1,5)) );

	selectedLight = 1;
	camptr = NULL;
	t = 0.0;

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

GRender::~GRender() {
	// TODO Auto-generated destructor stub
}

void GRender::start() {
	camera = shared_ptr<Camera>{ new Camera( shared_from_this(), mWnd ) };
	mWnd->addView( camera );

	ortho = shared_ptr<Ortho>{ new Ortho( shared_from_this(), mWnd ) };
	mWnd->addView( ortho );

	/*
	 * set uniforms
	 */
	UniformBlock<CameraProperties> camsky = skybox.getBlock<CameraProperties>( "Camera", 1 );
	camsky.assign( &camera->properties, 0 );

	skybox.setUniform("cubeTexture", &cubeTex->location);

	program.setUniform("cubeTexture", &cubeTex->location);
	program.setUniform("diffuseTexture", &brickTex->location);
	program.setUniform("normalTexture", &normalTex->location);
	program.setUniform("specularTexture", &woodDispTex->location);

	UniformBlock<CameraProperties> cam = program.getBlock<CameraProperties>( "Camera", 1 );
	cam.assign( &camera->properties, 0 );
	camptr = &camera->properties;
}

/*
 * TODO only call this once
 */
void GRender::prepare() {
	LightProperties &p = light.getLight(0);
	p.position = glm::vec4( 12.5f * sin(t), 8.0f, 12.5f * cos(t), 1.0 );
	light.updateLight(0);
	t += 0.01;

	shadow.enable();

	/*
	 * prepare depth map of each light
	 */
	light.clearDepthMap();
	light.createShadow(table);
	light.createShadow(box);
	light.createShadow(bunny);
	light.createShadow(sphere);
	light.createShadow(teapot);
	light.createShadow(torus);
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
	brickTex->enable(0);
	normalTex->enable(1);
	woodDispTex->enable(2);
	cubeTex->enable(3);

	program.enable();
	glEnable(GL_CULL_FACE);

	light.setLight();
	displayGeometry();

	light.drawIcons();
}

void GRender::displayUI() {
	glUseProgram(0);
	drawString( "test", 10, 10 );
}

void GRender::displayGeometry() {
	vb.enable();

	glUniform1i(useDiffTex, true);
	glUniform1i(useNormTex, true);
	woodTex->enable(0);
	woodNormTex->enable(1);
	woodDispTex->enable(2);
	drawObject(table);

	brickTex->enable(0);
	brickNormTex->enable(1);
	brickTex->enable(2);
	drawObject(box);

	glUniform1i(useDiffTex, false);
	glUniform1i(useNormTex, false);
	drawObject(bunny);
	drawObject(sphere);
	drawObject(teapot);

	glUniform1i(useNormTex, true);
	normalTex->enable(1);
	drawObject(torus);
}

void GRender::drawObject( shared_ptr<Geometry> g ) {
	light.setTransform(g->transform());
	camptr->data.M = g->transform();
	camptr->update();
	g->draw();
}

int GRender::mouseClicked( shared_ptr<ViewInterface> cam, int button, int state, int x, int y ) {
	if (state) {
		drag = false;
		return false;
	}

	glm::vec3 p = cam->project( glm::vec3(0,0,0) );
	getArc( p.x, p.y, x, y, 600.0, click_old );
	click_old = glm::inverse(cam->cameraAngle()) * click_old * cam->cameraAngle();
	drag = true;
	return true;
}

int GRender::mouseDragged(shared_ptr<ViewInterface> cam, int x, int y) {
	if (drag && selectedLight >= 0) {
		LightProperties &l = light.getLight(selectedLight);
		glm::vec3 p = cam->project( glm::vec3(0,0,0) );

		// modify orientation
		getArc(p.x, p.y, x, y, 600.0, click_new);
		click_new = glm::inverse(cam->cameraAngle()) * click_new * cam->cameraAngle();


		//getBoneAlignment(temp, in->cameraAngle(), click_new);
		glm::quat drag = click_new * glm::inverse(click_old);
		l.position = drag * l.position;

		//player.animation[0].modSelection( time, selectedBone, drag );
		light.updateLight(selectedLight);
		click_old = click_new;
		return true;
	}

	return false;
}

void GRender::messageSent(string) {

}

void GRender::keyPressed(unsigned char) {

}

} /* namespace std */
