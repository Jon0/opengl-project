#version 400

// Values that stay constant for the whole mesh
//uniform mat4 P;
//uniform mat4 V;
//uniform mat4 M;

uniform mat4 DepthBiasMVP [8];
uniform vec4 LightPosition_worldspace [8];
uniform bool useNormTex;

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;
layout(location = 3) in vec3 vertexTangent_modelspace;
layout(location = 4) in vec3 vertexBitangent_modelspace;

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

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec3 Position_worldspace;
out vec3 VertexNormal_tangentspace;

out vec3 EyeDirection_cameraspace;
out vec3 EyeDirection_tangentspace;

out vec3 LightSpotlight_cameraspace [8];
out vec3 LightSpotlight_tangentspace [8];
out vec3 LightDirection_cameraspace [8];
out vec3 LightDirection_tangentspace [8];

out vec4 ShadowCoord [8];

out mat4 MVP;
out mat3 MV3x3;
out mat3 TBN;



void main(){

	MVP = P * V * M;
	MV3x3 = mat3(V * M);

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4( vertexPosition_modelspace, 1 );

	// Position of the vertex, in worldspace : M * position
	Position_worldspace = (M * vec4(vertexPosition_modelspace,1)).xyz;

	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	vec3 vertexPosition_cameraspace = ( V * M * vec4(vertexPosition_modelspace,1)).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;


	// UV of the vertex. No special space for this one.
	UV = vertexUV;

	// model to camera = ModelView
	vec3 vertexTangent_cameraspace = MV3x3 * vertexTangent_modelspace;
	vec3 vertexBitangent_cameraspace = MV3x3 * vertexBitangent_modelspace;
	vec3 vertexNormal_cameraspace = MV3x3 * vertexNormal_modelspace;

	if (useNormTex) {
		TBN = transpose(mat3(
			vertexTangent_cameraspace,
			vertexBitangent_cameraspace,
			vertexNormal_cameraspace
		)); // You can use dot products instead of building this matrix and transposing it. See References for details.
	}
	else {
		TBN = mat3(1.0);
	}


	EyeDirection_tangentspace =  TBN * EyeDirection_cameraspace;
	VertexNormal_tangentspace = TBN * vertexNormal_cameraspace;


	/*
	 * per light operations
	 */
	 for (int light = 0; light < 3; ++light) {
		ShadowCoord[light] = DepthBiasMVP[light] * vec4(vertexPosition_modelspace, 1);

		// Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
		vec3 LightPosition_cameraspace = vec3(V * Lights[light].position);

		if (Lights[light].position.w > 0.1) {
			LightDirection_cameraspace[light] = LightPosition_cameraspace + EyeDirection_cameraspace;

			// get spotlight direction if needed
			if ( Lights[light].spotlight > 0.1 ) {
				vec3 SpotlightDirection_cameraspace = vec3(0,0,0) - vec3( V * Lights[light].direction );
				LightSpotlight_cameraspace[light] = LightPosition_cameraspace + SpotlightDirection_cameraspace;
				LightSpotlight_tangentspace[light] = TBN * LightSpotlight_cameraspace[light];
			}
		}
		else {
			LightDirection_cameraspace[light] = LightPosition_cameraspace;
		}

		LightDirection_tangentspace[light] = TBN * LightDirection_cameraspace[light];
	}
}
