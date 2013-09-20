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
			vb(9),
			g(),
			env(400.0),
			shader("shader/white.frag") {
	mWnd->start();
	env.init( &vb );
	vb.store();

	/*
	 * cube map
	 */
	env_tex = new Tex();
	env_tex->make3DTex("assets/image/sky2.png");

	box = new DrawList(g.readOBJ("assets/obj/Box.obj"), GL_TRIANGLES);
	bunny = new DrawList(g.readOBJ("assets/obj/Bunny.obj"), GL_TRIANGLES);
	table = new DrawList(g.readOBJ("assets/obj/Table.obj"), GL_TRIANGLES);
	teapot = new DrawList(g.readOBJ("assets/obj/Teapot.obj"), GL_TRIANGLES);
	torus = new DrawList(g.readOBJ("assets/obj/Torus.obj"), GL_TRIANGLES);

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glUseProgramObjectARB(shader.program);
}


Render::~Render() {
	// TODO Auto-generated destructor stub
}

void Render::start() {
	camera = shared_ptr<Camera>{ new Camera( shared_from_this(), mWnd ) };
	mWnd->addView( camera );
}

void Render::setLight() {
	// set lighting
	GLfloat lightPos[] = { -7.5f, 8.0f, -6.5f, 0.0f };
	GLfloat lightColorDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat lightColorAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColorDiffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightColorAmbient);

	GLfloat material_diffuse[] = { 0.45f, 0.45f, 0.45f, 1.0f };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material_diffuse);

	glEnable(GL_LIGHT0);
}

void Render::display( shared_ptr<ViewInterface>, chrono::duration<double> ) {
	glBindBuffer( GL_ARRAY_BUFFER, vb.addr() );
	glVertexPointer(3, GL_FLOAT, 9 * 4, NULL); //vertices
	glNormalPointer(GL_FLOAT, 9 * 4, (GLvoid *)(3*4));
	glTexCoordPointer(3, GL_FLOAT, 9 * 4, (GLvoid *)(6*4));
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	/*
	 * draw sky without lighting
	 */
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glColor3f(1.0f,1.0f,1.0f);

	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture( GL_TEXTURE_CUBE_MAP, env_tex->getAddr() );
	env.draw();
	glDisable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glColor3f(0.0f,1.0f,0.0f);

	setLight();
	box->display();
	bunny->display();
	table->display();
	teapot->display();
	torus->display();

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
