uniform mat4 mvp;
uniform mat4 modelView;
uniform mat4 mNormal;
attribute vec3 vpos;
attribute vec3 vcolor;
attribute vec2 vtex;
attribute vec3 vnormal;
varying vec3 fpos;
varying vec3 fcolor;
varying vec2 ftex;
varying vec3 N;
varying vec3 v;

void main() {
	gl_Position = mvp * vec4(vpos, 1);
	fpos = vpos;
	fcolor = vcolor;
	ftex = vtex;
	N = normalize(vec3(mNormal * vec4(vnormal, 0)));
	v = vec3(modelView * vec4(vpos, 1));
}