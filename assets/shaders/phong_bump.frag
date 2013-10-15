#version 420
#extension GL_NV_shader_buffer_load : enable

layout(std140) uniform LightProperties {
	vec4 position;
	vec4 color;
	vec4 direction;
	float intensity;
	float spotlight;
	float spotlightInner;
} Lights[8];

layout(std140) uniform Camera {
	uniform mat4 P;
	uniform mat4 V;
	uniform mat4 M;
};

layout(std140) uniform MaterialProperties {
	vec4 DiffuseColor;
	vec4 AmbientColor;
	vec4 SpecularColor;
	float Exponent;
} Material;

struct OctreeNode {
	// pointers to gpu memory
	OctreeNode *parent;
	OctreeNode *children [8];

	// node attributes
	vec4 normal;
	vec4 color;
	vec4 emission;
};

uniform OctreeNode *tree;


// Values that stay constant for the whole mesh.
layout(binding = 0, rgba8) coherent uniform image3D illumination;
uniform samplerCube cubeTexture;
uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;
uniform sampler2D specularTexture;
uniform sampler2DShadow shadowMap [8];
uniform bool useDiffTex;
uniform bool useNormTex;

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 Position_worldspace;
in vec3 VertexNormal_tangentspace;

in vec3 EyeDirection_cameraspace;
in vec3 EyeDirection_tangentspace;

in vec3 LightSpotlight_cameraspace [8];
in vec3 LightSpotlight_tangentspace [8];
in vec3 LightDirection_cameraspace [8];
in vec3 LightDirection_tangentspace [8];

in vec4 ShadowCoord [8];

in mat3 TBN;
in mat3 MV3x3;

// Ouput data
out vec4 color;

vec2 poissonDisk[16] = vec2[](
   vec2( -0.94201624 / 7000.0, -0.39906216 / 7000.0 ),
   vec2( 0.94558609 / 7000.0, -0.76890725 / 7000.0 ),
   vec2( -0.094184101 / 7000.0, -0.92938870 / 7000.0 ),
   vec2( 0.34495938 / 7000.0, 0.29387760 / 7000.0 ),
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

void main() {
	// Material properties
	vec4 MaterialDiffuseColor = Material.DiffuseColor;
	vec4 MaterialAmbientColor = Material.AmbientColor;
	vec4 MaterialSpecularColor = Material.SpecularColor;
	float MaterialExponent = Material.Exponent;
	if (useDiffTex) {
		MaterialDiffuseColor *= texture2D( diffuseTexture, UV );
		MaterialAmbientColor *= MaterialDiffuseColor;
		MaterialSpecularColor *= texture2D( specularTexture, UV );
	}

	// Local normal, in tangent space. V tex coordinate is inverted because normal map is in TGA (not in DDS) for better quality
	vec3 TextureNormal_tangentspace;
	if (useNormTex) {
		TextureNormal_tangentspace = normalize(texture2D( normalTexture, vec2(UV.x, -UV.y) ).rgb*2.0 - 1.0);
	}
	else {
		TextureNormal_tangentspace = VertexNormal_tangentspace;
	}

	  /*
	   *    Environment reflections
	   *	reflect ray around normal from eye to surface
	   */
	vec3 incident_eye = normalize ( EyeDirection_tangentspace );
	vec3 n = normalize ( TextureNormal_tangentspace );
	vec3 reflected = reflect (incident_eye, n);

	// convert from eye to world space
	reflected =  inverse(TBN) * reflected;
	reflected = vec3 (inverse (V*M) * vec4 (reflected, 0.0));
	vec4 ReflectionColor = texture(cubeTexture, reflected);
	ReflectionColor = vec4( pow(ReflectionColor.x, MaterialExponent),
							pow(ReflectionColor.y, MaterialExponent),
							pow(ReflectionColor.z, MaterialExponent), 1.0 ) * MaterialSpecularColor;

	// Eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_tangentspace);

	/*
	 *	*******************************
	 *	calculate for each light source
	 * 	*******************************
	 */
	vec4 DiffuseTotal = vec4(0.0);
	vec4 SpecularTotal = vec4(0.0);
	for (int light = 0; light < 3; ++light) {

		// Direction of the light (from the fragment to the light)
		vec3 l = normalize(LightDirection_tangentspace[light]);

		// Cosine of the angle between the normal and the light direction,
		float cosTheta = clamp( dot( n, l ), 0, 1 );

		// Direction in which the triangle reflects the light
		vec3 R = reflect( -l , n);

		// Cosine of the angle between the Eye vector and the Reflect vector,
		float cosAlpha = clamp( dot( E, R ), 0,1 );

		// Distance to the light
		float distance;
		if ( Lights[light].position.w > 0.0 ) {
			distance = length( Lights[light].position.xyz - Position_worldspace );
		}
		else {
			distance = 1.0;
		}

		/*
		 *	Shadows, Direct Visibility from light sources
		 */
		float bias = 0.005*tan( acos( cosTheta ) );
		bias = clamp(bias, 0.0, 0.0005);
		float visibility = 1.0;
		for (int i = 0; i < 4; i++){ //0.0625
			visibility -= 0.25*(1.0-texture( shadowMap[light], vec3(ShadowCoord[light].xy + poissonDisk[i],  (ShadowCoord[light].z-bias))/ShadowCoord[light].w ));
		}
		visibility = clamp( visibility, 0, 1 );

		/*
		 * Add indirect visibility
		 */

		// dampen spotlight by dot product angle
		if ( Lights[light].spotlight > 0.1 ) {
			float angle = dot( normalize(LightSpotlight_tangentspace[light]), normalize(LightDirection_tangentspace[light]));
			float spot = clamp((angle - Lights[light].spotlight) / (Lights[light].spotlightInner - Lights[light].spotlight), 0.0, 1.0);
			visibility = visibility * pow(spot, 2);

		}

		DiffuseTotal += MaterialDiffuseColor * Lights[light].color * Lights[light].intensity * visibility * cosTheta / (distance*distance);
		SpecularTotal += MaterialSpecularColor * Lights[light].color * Lights[light].intensity * visibility * pow(cosAlpha, MaterialExponent) / (distance*distance);
	}

	/*
	 *	*******************************
	 *	    set final color value
	 * 	*******************************
	 */

	//color = texture( illumination, vec3(0.5, 0.5, 0.5) + Position_worldspace / 512 ) + ReflectionColor + DiffuseTotal + SpecularTotal;
	//color = 0.05 * MaterialAmbientColor + ReflectionColor + DiffuseTotal + SpecularTotal;
	color = DiffuseTotal + SpecularTotal;
	color.w = 1.0;



}