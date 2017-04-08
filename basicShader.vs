#version 430

in vec3 position;
in vec4 color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec4 frag_color;
 
void main()
{
  gl_Position = Projection * View * Model * vec4(position, 1.0);
  frag_color = color;
}