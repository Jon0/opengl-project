/*
 * Render.cpp
 *
 *  Created on: 19/09/2013
 *      Author: remnanjona
 */

#include <iostream>
#include "Render.h"

namespace std {

Render::Render():
			mWnd{new MainWindow(800, 600, "Scene")},
			lighting(),
			vb(9),
			g(),
			env(400.0) {
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

	const unsigned char *p = glGetString(GL_VENDOR);
	const unsigned char *q = glGetString(GL_RENDERER);
	const unsigned char *r = glGetString(GL_VERSION);
	const unsigned char *s = glGetString(GL_SHADING_LANGUAGE_VERSION);
	cout << p << endl;
	cout << q << endl;
	cout << r << endl;
	cout << s << endl;


}


Render::~Render() {
	// TODO Auto-generated destructor stub
}

void Render::start() {
	camera = shared_ptr<Camera>{ new Camera( shared_from_this(), mWnd ) };
	mWnd->addView( camera );
}

void Render::drawObjects() {
	table->display();

	lighting.startTranslate(7.0, 2.0, 0.0);
	box->display();
	lighting.endTranslate();

	lighting.startTranslate(-5.0, 0.5, -2.0);
	bunny->display();
	lighting.endTranslate();

	lighting.startTranslate(-1.0, 0.5, 6.0);
	teapot->display();
	lighting.endTranslate();

	lighting.startTranslate(3.0, 1.0, -6.0);
	torus->display();
	lighting.endTranslate();
}

void Render::prepare() {
	lighting.prepareShadow();

	drawObjects();

	//Save modelview/projection matrice into texture7, also add a bias
	lighting.setTextureMatrix();
}

void Render::display( shared_ptr<ViewInterface>, chrono::duration<double> ) {
	// Now rendering from the camera POV, using the FBO to generate shadows
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);

	glViewport(0, 0, 800, 600);

	//Enabling color write (previously disabled for light POV z-buffer rendering)
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glDisable(GL_CULL_FACE);

	glUseProgram(0);

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
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture( GL_TEXTURE_CUBE_MAP, env_tex->getAddr() );
	env.draw();
	glDisable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glColor3f(1.0f,0.0f,0.0f);
	lighting.setLight();

	drawObjects();

	/*glUseProgram(0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-800.0 / 2, 800.0 / 2, -600.0 / 2, 600.0 / 2, 1, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor4f(1, 1, 1, 1);
	glActiveTextureARB(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthTextureId);
	glEnable(GL_TEXTURE_2D);
	glTranslated(0, 0, -1);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2d(1, 0);
	glVertex3f(800.0 / 2, 0, 0);
	glTexCoord2d(1, 1);
	glVertex3f(800.0 / 2, 600.0 / 2, 0);
	glTexCoord2d(0, 1);
	glVertex3f(0, 600.0 / 2, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);*/
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
