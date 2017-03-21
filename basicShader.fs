#version 330

varying vec4 vColor;
uniform vec4 color;

void main(void)
{
	gl_FragColor = vColor;
}