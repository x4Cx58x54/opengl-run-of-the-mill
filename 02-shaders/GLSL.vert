#version 330 core
layout(location = 0) in vec4 vPosition;
out vec4 color;
uniform float size;
uniform uint render_type;
void main()
{
    gl_Position = vec4(vPosition.x*size, vPosition.y*size, 1, 1);
    color = vec4(1, 1, 1, 1);
}
