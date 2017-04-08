#version 430

in vec4 frag_color;
in vec3 frag_normal;

out vec4 pixel_color;

void main()
{
   if(frag_normal != vec3(0, 0, 0)) {
   	pixel_color = vec4(frag_color.rgb
		* clamp(dot(-vec3(0, 0, 1), frag_normal), 0.0, 1.0), frag_color.a);
   } else {
	pixel_color = frag_color;
   }
}