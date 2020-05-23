#version 330 core

layout (location = 0) in vec4 t_pos;
layout (location = 1) in vec4 in_color;
out vec4 vs_color;

vec4 points = t_pos;

void translate(float dx, float dy, float dz)
{
    mat4 translate_mat = transpose(mat4(1, 0, 0, dx,
                                        0, 1, 0, dy,
                                        0, 0, 1, dz,
                                        0, 0, 0, 1));
    points = translate_mat * points;
}

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

void scale(float sx, float sy, float sz)
{
    mat4 scale_mat = mat4(sx, 0,  0,  0,
                          0,  sy, 0,  0,
                          0,  0,  sz, 0,
                          0,  0,  0,  1);
    points = scale_mat * points;
}

void main(void)
{
    rotate_y(20);
    rotate_x(15);
    translate(-0.3, -0.3, 0);
    gl_Position = points;
    vs_color = in_color;
}
