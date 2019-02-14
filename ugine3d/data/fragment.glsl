#define MAX_LIGHTS 2

uniform sampler2D texSampler;
uniform int isTexture;
uniform int numLights;
uniform vec4 diffuseColor;
uniform int shininess;
uniform vec3 ambientLight;
uniform vec4[MAX_LIGHTS] lightPosition;
uniform int[MAX_LIGHTS] lightType;
uniform vec3[MAX_LIGHTS] lightColor;
uniform float[MAX_LIGHTS] lightLinearAttenuation;
uniform float[MAX_LIGHTS] lightConstantAttenuation;
uniform float[MAX_LIGHTS] lightQuadraticAttenuation;
varying vec3 fpos;
varying vec3 fcolor;
varying vec2 ftex;
varying vec3 N;
varying vec3 v;

void main() {
	if (numLights > 0) {
		vec3 E = normalize(-v);
		vec3 finalDiffuse = ambientLight;
		vec3 finalSpecular = vec3(0,0,0);
		for(int i = 0; i < numLights; i++) {
			vec3 L = lightPosition[i].xyz;
			float attenuationFactor = 1;
			if (1 == lightType[i]) {
				L = L - v;
				float distance = length(L);
				attenuationFactor = 1 / (lightConstantAttenuation[i] + lightLinearAttenuation[i]*distance + lightQuadraticAttenuation[i]*distance*distance);
			}

			L = normalize(L);
			float NdotL = max(dot(N, L), 0);
			finalDiffuse = finalDiffuse + diffuseColor.xyz * NdotL;
			if (NdotL > 0) {
				vec3 H = normalize(E - L);
				float NdotH = max(dot(N, H), 0);
				finalSpecular = finalSpecular + pow(NdotH, shininess) * attenuationFactor * lightColor[i]; 
			}
		}

		if (0 == isTexture) {
			gl_FragColor = vec4(finalDiffuse * fcolor + finalSpecular, 1);
		} else {
			vec4 texColor = texture2D(texSampler, ftex);
			gl_FragColor = vec4(finalDiffuse * texColor.xyz + finalSpecular, texColor.w);
		}
	}
	else {
		if (0 == isTexture) {
			gl_FragColor = vec4(fcolor, 1);
		} else {
			gl_FragColor = texture2D(texSampler, ftex);
		}
	}
}
