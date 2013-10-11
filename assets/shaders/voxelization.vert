#version 420

//in vec3 vp;
layout(location = 0) in vec3 vertexPosition_modelspace;

out vec3 vertexPosition;

void main () {
	vertexPosition = vertexPosition_modelspace;
}