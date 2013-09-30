#version 400

//in vec3 vp;
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexUV;

layout(std140) uniform Camera {
	uniform mat4 P;
	uniform mat4 V;
	uniform mat4 M;
};

out vec3 texcoords;


void main () {
	mat4 MVP = P * V * M;
	gl_Position =  MVP * vec4( vertexPosition_modelspace, 1 );
	texcoords = vertexUV;
}