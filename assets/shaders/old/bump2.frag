#version 330 core

// New bumpmapping
in vec3 lightVec;
in vec3 halfVec;
in vec3 eyeVec;
in vec2 texCoord;

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 Position_worldspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

in vec3 LightDirection_tangentspace;
in vec3 EyeDirection_tangentspace;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform mat3 MV3x3;
uniform vec3 LightPosition_worldspace;

uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;


void main() {
	// lookup normal from normal map, move from [0,1] to  [-1, 1] range, normalize
	vec3 normal = 2.0 * texture2D (normalTexture, texCoord).rgb - 1.0;
	normal = normalize (normal);

	// compute diffuse lighting
	float lamberFactor= max (dot (lightVec, normal), 0.0) ;
	vec4 diffuseMaterial = vec4(0.0);
	vec4 diffuseLight  = vec4(0.0);

	// compute specular lighting
	vec4 specularMaterial ;
	vec4 specularLight ;
	float shininess ;

	// compute ambient
	vec4 ambientLight = vec4(0.2);

	if (lamberFactor > 0.0)
	{
		diffuseMaterial = texture2D (diffuseTexture, texCoord);
		diffuseLight  = vec4(0.8);

		// In doom3, specular value comes from a texture
		specularMaterial =  vec4(1.0)  ;
		specularLight  = vec4(0.8);
		shininess = pow (max (dot (halfVec, normal), 0.0), 2.0)  ;

		gl_FragColor =	diffuseMaterial * diffuseLight * lamberFactor ;
		gl_FragColor +=	specularMaterial * specularLight * shininess ;

	}

	gl_FragColor +=	ambientLight;

}