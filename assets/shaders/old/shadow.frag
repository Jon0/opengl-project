uniform sampler2D ShadowMap;

varying vec4 ShadowCoord;

varying vec3 N;
varying vec3 v;

void main()
	{
		vec4 shadowCoordinateWdivide = ShadowCoord / ShadowCoord.w ;

		// Used to lower moiré pattern and self-shadowing
		shadowCoordinateWdivide.z += 0.0005;

		float distanceFromLight = texture2D(ShadowMap,shadowCoordinateWdivide.st).z;


	 	float shadow = 1.0;
	 	if (ShadowCoord.w > 0.0)
	 		shadow = distanceFromLight < shadowCoordinateWdivide.z ? 0.5 : 1.0 ;


		//gl_FragColor =	 shadow * gl_Color;


		   vec3 L = normalize(gl_LightSource[0].position.xyz - v);
   		vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)
   		vec3 R = normalize(-reflect(L,N));

   		//calculate Ambient Term:
   		vec4 Iamb = gl_FrontLightProduct[0].ambient;

   		//calculate Diffuse Term:
   		vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0);
  		 Idiff = clamp(Idiff, 0.0, 1.0);

   		// calculate Specular Term:
  		 vec4 Ispec = gl_FrontLightProduct[0].specular
                * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);
   		Ispec = clamp(Ispec, 0.0, 1.0);
   		// write Total Color:
   		gl_FragColor = shadow * (gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec);



	}