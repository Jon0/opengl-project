#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 Position_worldspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;
in vec3 VertexNormal_tangentspace;
in vec4 ShadowCoord;

in vec3 LightDirection_tangentspace;
in vec3 EyeDirection_tangentspace;


// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;
uniform sampler2D specularTexture;
uniform sampler2DShadow shadowMap;
uniform mat4 V;
uniform mat4 M;
uniform mat3 MV3x3;
uniform vec3 LightPosition_worldspace;
uniform bool useDiffTex;
uniform bool useNormTex;

vec2 poissonDisk[16] = vec2[](
   vec2( -0.94201624, -0.39906216 ),
   vec2( 0.94558609, -0.76890725 ),
   vec2( -0.094184101, -0.92938870 ),
   vec2( 0.34495938, 0.29387760 ),
   vec2( -0.91588581, 0.45771432 ),
   vec2( -0.81544232, -0.87912464 ),
   vec2( -0.38277543, 0.27676845 ),
   vec2( 0.97484398, 0.75648379 ),
   vec2( 0.44323325, -0.97511554 ),
   vec2( 0.53742981, -0.47373420 ),
   vec2( -0.26496911, -0.41893023 ),
   vec2( 0.79197514, 0.19090188 ),
   vec2( -0.24188840, 0.99706507 ),
   vec2( -0.81409955, 0.91437590 ),
   vec2( 0.19984126, 0.78641367 ),
   vec2( 0.14383161, -0.14100790 )
);

void main(){

	// Light emission properties
	// You probably want to put them as uniforms
	vec3 LightColor = vec3(1,1,1);
	float LightPower = 80.0;

	// Material properties
	vec3 MaterialDiffuseColor;
	vec3 MaterialAmbientColor;
	vec3 MaterialSpecularColor;
	if (useDiffTex) {
		MaterialDiffuseColor = texture2D( diffuseTexture, UV ).rgb;
		MaterialAmbientColor = MaterialDiffuseColor * 0.2;
		MaterialSpecularColor = texture2D( specularTexture, UV ).rgb * 0.9;
	}
	else {
		MaterialDiffuseColor = vec3(1, 0, 0);
		MaterialAmbientColor = MaterialDiffuseColor * 0.2;
		MaterialSpecularColor = vec3(0.9, 0, 0);
	}


	// Local normal, in tangent space. V tex coordinate is inverted because normal map is in TGA (not in DDS) for better quality
	vec3 TextureNormal_tangentspace;
	if (useNormTex) {
		TextureNormal_tangentspace = normalize(texture2D( normalTexture, vec2(UV.x, -UV.y) ).rgb*2.0 - 1.0);
	}
	else {
		TextureNormal_tangentspace = VertexNormal_tangentspace;
	}


	// Distance to the light
	float distance = length( LightPosition_worldspace - Position_worldspace );

	// Normal of the computed fragment, in camera space
	vec3 n = normalize(TextureNormal_tangentspace);

	// Direction of the light (from the fragment to the light)
	vec3 l = normalize(LightDirection_tangentspace);

	// Cosine of the angle between the normal and the light direction,
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp( dot( n,l ), 0, 1 );

	// Eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_tangentspace);

	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l, n);

	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp( dot( E,R ), 0,1 );

	//float visibility = texture( shadowMap, vec3(ShadowCoord.xy, (ShadowCoord.z)/ShadowCoord.w) );

	float bias = 0.0005*tan(acos(cosTheta));
	bias = clamp(bias, 0,0.001);

	float visibility = 1.0;
	for (int i=0;i<16;i++){
		visibility -= 0.04*(1.0-texture( shadowMap, vec3(ShadowCoord.xy + poissonDisk[i]/700.0,  (ShadowCoord.z-bias)/ShadowCoord.w) ));
	}
	visibility = clamp( visibility, 0, 1 );

	color =
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * LightColor * LightPower * visibility * cosTheta / (distance*distance) +
		// Specular : reflective highlight, like a mirror
		MaterialSpecularColor * LightColor * LightPower * visibility * pow(cosAlpha, 5) / (distance*distance);

}