uniform sampler2D texSampler;
uniform int isTexture;
varying vec3 fcolor;
varying vec2 ftex;

void main() {
	if (0 == isTexture) {
		gl_FragColor = vec4(fcolor, 1);
	} else {
		gl_FragColor = texture2D(texSampler, ftex);
	}
}
