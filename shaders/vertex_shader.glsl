#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
out vec3 Color;
uniform mat4 view;
uniform mat4 proj;
void main()
{
    Color = color;
    gl_Position = proj * view * vec4(position, 1.0);
}