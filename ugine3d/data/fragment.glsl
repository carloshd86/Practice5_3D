uniform sampler2D texSampler;
uniform int isTexture;
uniform int[] ligthType;
uniform vec3[] ligthColor;
uniform float[] ligthLinearAttenuation;
varying vec3 fcolor;
varying vec2 ftex;
varying vec3 fnormal;

void main() {
	if (0 == isTexture) {
		gl_FragColor = vec4(fcolor, 1);
	} else {
		gl_FragColor = texture2D(texSampler, ftex);
	}
}
