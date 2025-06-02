#version 410

layout (location = 0) in vec2 vp;
layout (location = 1) in vec2 vt;

out vec2 texture_coords;
uniform float layer_z;

void main () {
	texture_coords = vt;
	gl_Position = vec4 (vp, layer_z, 1.0);
}
