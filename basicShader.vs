#version 430

attribute vec4 position;
uniform mat4 matrix;

void main(void)
{
      gl_Position = matrix * position;
}