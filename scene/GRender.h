/*
 * GRender.h
 *
 *  Created on: 23/09/2013
 *      Author: remnanjona
 */

#ifndef GRENDER_H_
#define GRENDER_H_

#include <memory>
#include <vector>

#include "../geometry/DrawList.h"
#include "../geometry/Geometry.h"
#include "../load/SkeletonLoader.h"
#include "../pipeline/Step.h"
#include "../shader/Program.h"
#include "../view/Camera.h"
#include "../view/Ortho.h"
#include "../window/MainWindow.h"
#include "SceneInterface.h"

namespace std {

class LightingModel;

class GRender:
		public enable_shared_from_this<GRender>,
		public SceneInterface
{
public:
	LightingModel *lightmodel;
	shared_ptr<DrawList> model;
	vector< shared_ptr<Geometry> > objects;
	SkeletonLoader sload;
	shared_ptr<Skeleton> skel;
	pose current_pose;

	/*
	 * select and control
	 */
	bool drag, showIcons;
	int selectedLight;
	glm::quat click_old, click_new;
	float *selFloat;
	glm::vec4 *selVec;

	string message;

	GRender( VertexBuffer & );
	virtual ~GRender();

	void displayGeometry( UBO<CameraProperties> &, UniformBlock<MaterialProperties> & );
	void drawObject( shared_ptr<Geometry>, UBO<CameraProperties> &, UniformBlock<MaterialProperties> & );
	void setSelection(glm::vec4 *, string);
	void setLightModel( LightingModel * );
	void debug( shared_ptr<ViewInterface> );

	virtual vector< shared_ptr<Geometry> > &content();
	virtual void update( chrono::duration<double> );
	virtual void displayUI();
	virtual int mouseClicked( shared_ptr<ViewInterface>, int, int, int, int );
	virtual int mouseDragged( shared_ptr<ViewInterface>, int, int );
	virtual void messageSent(string);
	virtual void keyPressed(unsigned char);

};

} /* namespace std */
#endif /* GRENDER_H_ */
