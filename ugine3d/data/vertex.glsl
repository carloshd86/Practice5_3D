uniform mat4 mvp;
attribute vec3 vpos;
attribute vec3 vcolor;
attribute vec2 vtex;
attribute vec3 vnormal;
varying vec3 fcolor;
varying vec2 ftex;
varying vec3 fnormal;

void main() {
	gl_Position = mvp * vec4(vpos, 1);
	fcolor = vcolor;
	ftex = vtex;
}