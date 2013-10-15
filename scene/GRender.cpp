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

GRender::GRender( VertexBuffer &vb ):
  skel { sload.readASF( "assets/Avatar/priman.asf" ) }
{
    model = readGeometry("assets/Avatar/andy.obj");

    GMesh *gm = &model->data.data()[6]; //model->getMesh(0);
    gm->texture = new Tex();
    gm->texture->make2DTex("assets/Avatar/boySmiley.jpg");
    gm->texaddr = gm->texture->getAddr();

    objects.push_back(model);
	objects.push_back( readGeometry("assets/Sponza/SponzaTri.obj") );
	//objects.push_back( readGeometry("assets/obj/Box.obj") );
	//objects.push_back( readGeometry("assets/obj/Bunny.obj") );
	//objects.push_back( readGeometry("assets/obj/Sphere.obj") );
	//objects.push_back( readGeometry("assets/obj/Table.obj") );
	//objects.push_back( readGeometry("assets/obj/Teapot.obj") );
	//objects.push_back( readGeometry("assets/obj/Torus.obj") );

	/* set skel pose */
	makeState( skel->getNumBones(), &current_pose );
	current_pose.adjust = glm::vec3(0.0, 18.0, 5.0);

	// setup VBO, and lighting tracking
	for (auto &g: objects) {
		g->init(&vb);
	}

	//	model->setTransform(glm::translate(glm::mat4(1.0),glm::vec3(0.0,0.0,0.0)));
	model->setTransform(glm::translate(glm::mat4(1.0), glm::vec3(0.0,15.0,0.0))*glm::scale(glm::mat4(1.0), glm::vec3(.015)));

	/*
	 * selection
	 */
	lightmodel = NULL;
	selectedLight = 1;
	selFloat = NULL;
	selVec = NULL;
	drag = false;

	message = "Light "+to_string(selectedLight) +" : Position";
	showIcons = true;
}

GRender::~GRender() {
	// TODO Auto-generated destructor stub
}

void GRender::setLightModel( LightingModel *lm ) {
	lightmodel = lm;

	LightProperties &l = lightmodel->getLight(selectedLight);
	selVec = &l.position;
}

vector< shared_ptr<Geometry> > &GRender::content() {
	return objects;
}

void GRender::update( chrono::duration<double> ) {
	// update scene
}

void GRender::debug( shared_ptr<ViewInterface> c ) {

	/*
	 * do some fixed pipeline rendering
	 */
	if (showIcons) {

		glUseProgram(0);
		skel->setCurrentPose(&current_pose);
		skel->display();

		lightmodel->drawIcons();
	}
}

void GRender::displayUI() {
	drawString( message, 10, 10 );
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
		lightmodel->updateLight(selectedLight);
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
		lightmodel->updateLight(selectedLight);
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
	cout << message << endl;
}

void GRender::keyPressed(unsigned char c) {
	LightProperties &l = lightmodel->getLight(selectedLight);
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
		setSelection( &lightmodel->getLight(selectedLight).position, "Position" );
		break;

	/*
	 * Spotlight specific controls
	 */
	case 't':
		l.spotlight *= 1.01;
		if (l.spotlight > l.spotlightInner) l.spotlightInner = l.spotlight;
		lightmodel->updateLight(selectedLight);
		break;
	case 'y':
		l.spotlight /= 1.01;
		lightmodel->updateLight(selectedLight);
		break;
	case 'g':
		l.spotlightInner *= 1.01;
		lightmodel->updateLight(selectedLight);
		break;
	case 'h':
		l.spotlightInner /= 1.01;
		if (l.spotlight > l.spotlightInner) l.spotlight = l.spotlightInner;
		lightmodel->updateLight(selectedLight);
		break;
	case '.':
		showIcons = !showIcons;
		break;
	case ',':
		for (int i = 0; i < 3; ++i) {
			LightProperties &l = lightmodel->getLight(i);
			cout << "color " << l.color.w << ", " << l.color.x << ", " << l.color.y << ", " << l.color.z << endl;
			cout << "position " << l.position.w << ", " << l.position.x << ", " << l.position.y << ", " << l.position.z << endl;
			cout << "direction " << l.direction.w << ", " << l.direction.x << ", " << l.direction.y << ", " << l.direction.z << endl;
			cout << "intensity " << l.intensity << endl;
		}
		break;
	}
}

} /* namespace std */
