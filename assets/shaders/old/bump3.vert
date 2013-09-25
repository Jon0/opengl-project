attribute vec3 tangent;
attribute vec3 binormal;
varying vec3 position;
varying vec3 lightvec;

void main()
{
	gl_Position = ftransform();
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
 	position = gl_Vertex.xyz;
	mat3 TBNMatrix = mat3(tangent, binormal, gl_Normal);
 	lightvec = gl_LightSource[0].position.xyz - position;
	lightvec *= TBNMatrix;
}