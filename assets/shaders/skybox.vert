#version 400

//in vec3 vp;
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexUV;

out vec3 texcoords;

uniform mat4 MVP;

void main () {
  //texcoords = vertexPosition_modelspace;
  //gl_Position = P * V * vec4 (vertexPosition_modelspace, 1.0);

	gl_Position =  MVP * vec4( vertexPosition_modelspace, 1 );
	texcoords = vertexUV;
}