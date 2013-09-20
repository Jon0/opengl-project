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
			vb(9),
			g(),
			env(400.0),
			vert("shader/shadow.vert", GL_VERTEX_SHADER),
			frag("shader/shadow.frag", GL_FRAGMENT_SHADER) {
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


	const unsigned char *p = glGetString(GL_VENDOR);
	const unsigned char *q = glGetString(GL_RENDERER);
	const unsigned char *r = glGetString(GL_VERSION);
	const unsigned char *s = glGetString(GL_SHADING_LANGUAGE_VERSION);
	cout << p << endl;
	cout << q << endl;
	cout << r << endl;
	cout << s << endl;




	shadowMapWidth = 800 * 2;
	shadowMapHeight = 600 * 2;
	generateShadowFBO();

	glEnable(GL_CULL_FACE);

	//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	//Create a program handle.
	program = glCreateProgram();

	//Attach the shaders. Here, assume that fragmentHandle is a handle to a fragment shader object,
	//and that vertexHandle is a handle to a vertex shader object.
	glAttachShader(program, vert.ShaderHandle);
	glAttachShader(program, frag.ShaderHandle);

	//Link the program.
	glLinkProgram(program);

	shadowMapUniform = glGetUniformLocation(program,"ShadowMap");
}


Render::~Render() {
	// TODO Auto-generated destructor stub
}

void Render::start() {
	camera = shared_ptr<Camera>{ new Camera( shared_from_this(), mWnd ) };
	mWnd->addView( camera );
}

void Render::generateShadowFBO() {
	GLenum FBOstatus;

	// Try to use a texture depth component
	glGenTextures(1, &depthTextureId);
	glBindTexture(GL_TEXTURE_2D, depthTextureId);

	// GL_LINEAR does not make sense for depth texture. However, next tutorial shows usage of GL_LINEAR and PCF
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Remove artifact on the edges of the shadowmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// No need to force GL_DEPTH_COMPONENT24, drivers usually give you the max precision if available
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth,
			shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// create a framebuffer object
	glGenFramebuffersEXT(1, &fboId);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);

	// Instruct openGL that we won't bind a color texture with the currently bound FBO
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// attach the texture to FBO depth attachment point
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,
			GL_TEXTURE_2D, depthTextureId, 0);

	// check FBO status
	FBOstatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if (FBOstatus != GL_FRAMEBUFFER_COMPLETE_EXT)
		printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");

	// switch back to window-system-provided framebuffer
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void Render::setTextureMatrix() {
	static double modelView[16];
	static double projection[16];

	// Moving from unit cube [-1,1] to [0,1]
	const GLdouble bias[16] = {
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0 };

	// Grab modelview and transformation matrices
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	glMatrixMode(GL_TEXTURE);
	glActiveTexture(GL_TEXTURE7);

	glLoadIdentity();
	glLoadMatrixd(bias);

	// concatating all matrices into one.
	glMultMatrixd(projection);
	glMultMatrixd(modelView);

	// Go back to normal matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void Render::setLight() {
	// set lighting
	GLfloat lightPos[] = { -7.5f * 3, 8.0f, -6.5f, 0.0f };
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

// During translation, we also have to maintain the GL_TEXTURE8, used in the shadow shader
// to determine if a vertex is in the shadow.
void Render::startTranslate(float x,float y,float z)
{
	glPushMatrix();
	glTranslatef(x,y,z);

	glMatrixMode(GL_TEXTURE);
	glActiveTextureARB(GL_TEXTURE7);
	glPushMatrix();
	glTranslatef(x,y,z);
}

void Render::endTranslate() {
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Render::drawObjects() {
	table->display();

	startTranslate(7.0, 2.0, 0.0);
	box->display();
	endTranslate();

	startTranslate(-5.0, 0.5, -2.0);
	bunny->display();
	endTranslate();



	startTranslate(-1.0, 0.5, 6.0);
	teapot->display();
	endTranslate();

	startTranslate(3.0, 1.0, -6.0);
	torus->display();
	endTranslate();
}

void Render::prepare() {
	//First step: Render from the light POV to a FBO, story depth values only
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId);	//Rendering offscreen

	//Using the fixed pipeline to render to the depthbuffer
	glUseProgram(0);

	// In the case we render the shadowmap to a higher resolution, the viewport must be modified accordingly.
	glViewport(0, 0, shadowMapWidth, shadowMapHeight);

	// Clear previous frame values
	glClear( GL_DEPTH_BUFFER_BIT);

	//Disable color rendering, we only want to write to the Z-Buffer
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 800.0/600.0, 10.0, 40000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-7.5f * 3, 8.0f, -6.5f, 0,0,0, 0,1,0);

	// Culling switching, rendering only backface, this is done to avoid self-shadowing
	glCullFace(GL_FRONT);

	drawObjects();

	//Save modelview/projection matrice into texture7, also add a bias
	setTextureMatrix();

}

void Render::display( shared_ptr<ViewInterface>, chrono::duration<double> ) {
	// Now rendering from the camera POV, using the FBO to generate shadows
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);

	glViewport(0, 0, 800, 600);

	//Enabling color write (previously disabled for light POV z-buffer rendering)
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glCullFace(GL_BACK);

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
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture( GL_TEXTURE_CUBE_MAP, env_tex->getAddr() );
	env.draw();
	glDisable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glColor3f(1.0f,0.0f,0.0f);
	setLight();

	//Using the shadow shader
	glUseProgram(program);
	glUniform1i(shadowMapUniform, 7);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D,depthTextureId);

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
