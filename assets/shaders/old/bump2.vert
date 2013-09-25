#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 in_Vertex;
layout(location = 1) in vec2 in_TexCoord_3;
layout(location = 2) in vec3 in_Normal;
layout(location = 3) in vec3 tangent;

out vec3 lightVec;
out vec3 halfVec;
out vec3 eyeVec;
out vec2 texCoord;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform mat3 MV3x3;
uniform vec3 LightPosition_worldspace;

void main()
{
	texCoord =  vec2(in_TexCoord_3[0], in_TexCoord_3[1]);

	// Building the matrix Eye Space -> Tangent Space
	vec3 n = normalize (MV3x3 * in_Normal);
	vec3 t = normalize (MV3x3 * tangent);
	vec3 b = cross (n, t);

	vec4 inPosition = vec4(in_Vertex, 1.0);
	vec3 vertexPosition = vec3(MVP *  inPosition);
	vec3 lightDir = normalize(LightPosition_worldspace - vertexPosition);


	// transform light and half angle vectors by tangent basis
	vec3 v;
	v.x = dot (lightDir, t);
	v.y = dot (lightDir, b);
	v.z = dot (lightDir, n);
	lightVec = normalize (v);


	v.x = dot (vertexPosition, t);
	v.y = dot (vertexPosition, b);
	v.z = dot (vertexPosition, n);
	eyeVec = normalize (v);


	vertexPosition = normalize(vertexPosition);

	/* Normalize the halfVector to pass it to the fragment shader */

	// No need to divide by two, the result is normalized anyway.
	// vec3 halfVector = normalize((vertexPosition + lightDir) / 2.0);
	vec3 halfVector = normalize(vertexPosition + lightDir);
	v.x = dot (halfVector, t);
	v.y = dot (halfVector, b);
	v.z = dot (halfVector, n);

	// No need to normalize, t,b,n and halfVector are normal vectors.
	//normalize (v);
	halfVec = v ;


	gl_Position = MVP * inPosition;
}