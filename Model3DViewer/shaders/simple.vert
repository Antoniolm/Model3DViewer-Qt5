#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
out vec4 inColor;

uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position =  projection * view * vec4(position, 1.0);
  inColor = vec4(color, 1.0f);
}
