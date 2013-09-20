/*
 * Render.cpp
 *
 *  Created on: 19/09/2013
 *      Author: remnanjona
 */

#include "Render.h"

namespace std {

Render::Render():
			mWnd{new MainWindow(800, 600, "Scene")},
			g() {
	mWnd->start();

	box = new DrawList(g.readOBJ("assets/obj/Box.obj"), GL_TRIANGLES);
	bunny = new DrawList(g.readOBJ("assets/obj/Bunny.obj"), GL_TRIANGLES);
	table = new DrawList(g.readOBJ("assets/obj/Table.obj"), GL_TRIANGLES);
	teapot = new DrawList(g.readOBJ("assets/obj/Teapot.obj"), GL_TRIANGLES);
	torus = new DrawList(g.readOBJ("assets/obj/Torus.obj"), GL_TRIANGLES);
}


Render::~Render() {
	// TODO Auto-generated destructor stub
}

void Render::start() {
	camera = shared_ptr<Camera>{ new Camera( shared_from_this(), mWnd ) };
	mWnd->addView( camera );
}

void Render::setLight() {
	float direction[] = { 0.0f, 0.0f, 1.0f, 0.0f };
	float diffintensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, direction);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffintensity);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	GLfloat material_diffuse[] = { 0.45f, 0.45f, 0.45f, 1.0f };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material_diffuse);

	glEnable(GL_LIGHT0);
}

void Render::display( shared_ptr<ViewInterface>, chrono::duration<double> ) {
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glColor3f(0.0f,1.0f,0.0f);
	//glColor3f(0.0, 0.5+0.5*sin(rotation/360.0), 0.5+0.5*cos(rotation/360.0));

	setLight();
	box->display();
	bunny->display();
	table->display();
	teapot->display();
	torus->display();

	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
}

int Render::mouseClicked( shared_ptr<ViewInterface>, int, int, int, int ) {
	return false;
}

int Render::mouseDragged( shared_ptr<ViewInterface>, int, int ) {
	return false;
}

void Render::messageSent(string) {

}

void Render::keyPressed(unsigned char) {

}

} /* namespace std */
