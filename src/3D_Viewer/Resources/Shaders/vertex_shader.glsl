#version 120
attribute vec3 coord3d;
uniform vec4 color;
uniform mat4 MVP_Matrix;

varying vec4 color_out;

void main() {
   color_out=color;
   gl_Position = MVP_Matrix * vec4(coord3d.x, coord3d.y, coord3d.z, 1.0);
}
