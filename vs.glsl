#version 410

layout (location = 0) in vec2 vp;
layout (location = 1) in vec2 vt;

out vec2 texture_coords;
uniform float offsetz;

void main () {
	texture_coords = vt;
	gl_Position = vec4 (vp, offsetz, 1.0);
}
