/*
 * Render.h
 *
 *  Created on: 19/09/2013
 *      Author: remnanjona
 */

#ifndef RENDER_H_
#define RENDER_H_

#include <memory>
#include "SceneInterface.h"
#include "../buffer/VertexBuffer.h"
#include "../geometry/Cube.h"
#include "../geometry/DrawList.h"
#include "../load/GeometryLoader.h"
#include "../shader/Shader.h"
#include "../texture/Tex.h"
#include "../view/Camera.h"
#include "../window/MainWindow.h"

namespace std {

class Render:
		public enable_shared_from_this<Render>,
		public SceneInterface {
public:
	Render();
	virtual ~Render();

	void start();
	void generateShadowFBO();
	void setTextureMatrix();
	void setLight();

	void startTranslate(float,float,float);
	void endTranslate();
	void drawObjects();

	virtual void prepare();
	virtual void display( shared_ptr<ViewInterface>, chrono::duration<double> );
	virtual int mouseClicked( shared_ptr<ViewInterface>, int, int, int, int );
	virtual int mouseDragged( shared_ptr<ViewInterface>, int, int );
	virtual void messageSent(string);
	virtual void keyPressed(unsigned char);

	shared_ptr<MainWindow> mWnd;
	shared_ptr<Camera> camera;
	VertexBuffer vb;
	GeometryLoader g;
	Cube env;

	/*
	 * shaders
	 */
	GLhandleARB program;
	Shader vert;
	Shader frag;

	Tex *env_tex;

	DrawList *box;
	DrawList *bunny;
	DrawList *table;
	DrawList *teapot;
	DrawList *torus;


	int shadowMapWidth;
	int shadowMapHeight;

	// Hold id of the framebuffer for light POV rendering
	GLuint fboId;

	// Z values will be rendered to this texture when using fboId framebuffer
	GLuint depthTextureId;

	GLuint shadowMapUniform;


};

} /* namespace std */
#endif /* RENDER_H_ */
