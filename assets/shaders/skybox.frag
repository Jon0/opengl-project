#version 400

uniform samplerCube cubeTexture;

in vec3 texcoords;

out vec4 frag_colour;

void main () {
	frag_colour = texture (cubeTexture, texcoords);
}