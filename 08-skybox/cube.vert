#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 Position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

vec4 points = vec4(aPos, 1.0);

void rotate_x(float deg)
{
    float rad = radians(deg);
    float c = cos(rad);
    float s = sin(rad);
    mat4 rotate_x_mat = mat4(1, 0,  0, 0,
                             0, c, -s, 0,
                             0, s,  c, 0,
                             0, 0,  0, 1);
    points = rotate_x_mat * points;
}
void rotate_y(float deg)
{
    float rad = radians(deg);
    float c = cos(rad);
    float s = sin(rad);
    mat4 rotate_y_mat = mat4(c, 0, -s, 0,
                             0, 1,  0, 0,
                             s, 0,  c, 0,
                             0, 0,  0, 1);
    points = rotate_y_mat * points;
}
void rotate_z(float deg)
{
    float rad = radians(deg);
    float c = cos(rad);
    float s = sin(rad);
    mat4 rotate_z_mat = mat4(c, -s, 0, 0,
                             s,  c, 0, 0,
                             0,  0, 1, 0,
                             0,  0, 0, 1);
    points = rotate_z_mat * points;
}

void main()
{
    rotate_x(20);
    rotate_y(-30);
    Normal = mat3(transpose(inverse(model))) * aNormal;
    Position = vec3(model * points);
    gl_Position = projection * view * model * points;
}
