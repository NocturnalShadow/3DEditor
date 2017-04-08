#version 430

in vec4 frag_color;
out vec4 pixel_color;

void main()
{
   pixel_color = frag_color;
}