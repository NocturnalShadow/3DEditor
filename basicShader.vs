attribute vec4 vertex;
uniform mat4 matrix;
void main(void)
{
      gl_Position = matrix * vertex;
}