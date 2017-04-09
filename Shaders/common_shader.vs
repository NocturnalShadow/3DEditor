#version 430

in vec3 position;
in vec4 color;
in vec3 normal;
in vec2 texture;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 frag_normal;
out vec4 frag_color; 

void main()
{
  mat4 Transform = Projection * View * Model;
  gl_Position = Transform * vec4(position, 1.0);
  frag_normal = (Transform * vec4(normal, 0.0)).xyz;
  frag_color  = color;
}