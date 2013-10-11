/*
 * GRender.cpp
 *
 *  Created on: 23/09/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "../geometry/Cube.h"
#include "../load/GeometryLoader.h"
#include "../texture/Font.h"
#include "GRender.h"

namespace std {

GRender::GRender():
		program("phong_bump"),
		shadow("shadow_depth"),
		skybox("skybox"),
		vb(15),
		sky { new Cube(500) },
		light { shadow, program },
		camsky { skybox.getBlock<CameraProperties>( "Camera", 1 ) },
		cam { program.getBlock<CameraProperties>( "Camera", 1 ) },
		materialUniform { program.getBlock<MaterialProperties>("MaterialProperties", 1) }
{
	objects.push_back( readGeometry("assets/Sponza/SponzaTri.obj") );
	//objects.push_back( readGeometry("assets/obj/Box.obj") );
	objects.push_back( readGeometry("assets/obj/Bunny.obj") );
	//objects.push_back( readGeometry("assets/obj/Sphere.obj") );
	//objects.push_back( readGeometry("assets/obj/Table.obj") );
	//objects.push_back( readGeometry("assets/obj/Teapot.obj") );
	//objects.push_back( readGeometry("assets/obj/Torus.obj") );

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

	// setup VBO, and lighting tracking
	sky->init(&vb);
	for (auto &g: objects) {
		g->init(&vb);
		light.track( g );
	}
	vb.store();

	/*
	 * set uniforms
	 */
	skybox.setUniform("cubeTexture", &cubeTex->location);

	program.setUniform("cubeTexture", &cubeTex->location);
	program.setUniform("diffuseTexture", &brickTex->location);
	program.setUniform("normalTexture", &normalTex->location);
	program.setUniform("specularTexture", &woodDispTex->location);

	/*
	 * selection
	 */
	selectedLight = 1;
	LightProperties &l = light.getLight(selectedLight);
	selFloat = NULL;
	selVec = &l.position;
	drag = false;

	message = "Light "+to_string(selectedLight) +" : Position";
	showIcons = true;
	t = 0.0;

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

GRender::~GRender() {
	// TODO Auto-generated destructor stub
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
	for (auto &g: objects) light.createShadow(g);
}

void GRender::display( shared_ptr<ViewInterface> c, chrono::duration<double> ) {
	cubeTex->enable(0);

	/* TODO translate by camera position */
	glDisable(GL_CULL_FACE);
	skybox.enable();
	camsky.assign( c->properties() );
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
	cam.assign( c->properties() );

	light.setLight();
	displayGeometry( c->properties() );

	if (showIcons) light.drawIcons();
}

void GRender::displayUI() {
	drawString( message, 10, 10 );
}

void GRender::displayGeometry( UBO<CameraProperties> *camptr ) {
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	vb.enable();

	glUniform1i(useDiffTex, false);
	glUniform1i(useNormTex, false);

	for (auto &g: objects) drawObject(g, camptr);
}

void GRender::drawObject( shared_ptr<Geometry> g, UBO<CameraProperties> *camptr ) {
	materialUniform.assign(g->materialUBO());

	//light.setTransform(g->transform());
	camptr->data.M = g->transform();
	camptr->update();
	g->draw();
}

int GRender::mouseClicked( shared_ptr<ViewInterface> cam, int button, int state, int x, int y ) {
	if (state) {
		drag = false;
		return false;
	}

	if (button == 0) {
		glm::vec3 p = cam->project(glm::vec3(0, 0, 0));
		getArc(p.x, p.y, x, y, 600.0, click_old);
		click_old = glm::inverse(cam->cameraAngle()) * click_old * cam->cameraAngle();
		drag = true;
		return true;
	}

	if (selVec) {
		if (button == 3) {
			selVec->x *= 1.05;
			selVec->y *= 1.05;
			selVec->z *= 1.05;
		} else if (button == 4) {
			selVec->x /= 1.05;
			selVec->y /= 1.05;
			selVec->z /= 1.05;
		}
		light.updateLight(selectedLight);
		return true;
	}

	return false;
}

int GRender::mouseDragged(shared_ptr<ViewInterface> cam, int x, int y) {
	if (drag && selVec) {
		glm::vec3 p = cam->project( glm::vec3(0,0,0) );

		// modify orientation
		getArc(p.x, p.y, x, y, 600.0, click_new);
		click_new = glm::inverse(cam->cameraAngle()) * click_new * cam->cameraAngle();
		glm::quat drag = click_new * glm::inverse(click_old);

		/*
		 * update selected variable
		 */
		*selVec = drag * *selVec;
		light.updateLight(selectedLight);
		click_old = click_new;
		return true;
	}

	return false;
}

void GRender::messageSent(string) {

}

void GRender::setSelection(glm::vec4 *i, string type) {
	selVec = i;
	message = "Light "+to_string(selectedLight) + " : " + type;
}

void GRender::keyPressed(unsigned char c) {
	LightProperties &l = light.getLight(selectedLight);
	switch (c) {
	case 'a':
		setSelection(&l.position, "Position");
		break;
	case 's':
		setSelection(&l.direction, "Spot");
		break;
	case 'd':
		setSelection(&l.color, "Color");
		break;
	case 'z':
		selectedLight = (selectedLight + 1) % 3;
		setSelection( &light.getLight(selectedLight).position, "Position" );
		break;

	/*
	 * Spotlight specific controls
	 */
	case 't':
		l.spotlight *= 1.01;
		if (l.spotlight > l.spotlightInner) l.spotlightInner = l.spotlight;
		light.updateLight(selectedLight);
		break;
	case 'y':
		l.spotlight /= 1.01;
		light.updateLight(selectedLight);
		break;
	case 'g':
		l.spotlightInner *= 1.01;
		light.updateLight(selectedLight);
		break;
	case 'h':
		l.spotlightInner /= 1.01;
		if (l.spotlight > l.spotlightInner) l.spotlight = l.spotlightInner;
		light.updateLight(selectedLight);
		break;
	case '.':
		showIcons = !showIcons;
		break;
	}
}

} /* namespace std */
