#version 330 core
uniform mat4 model_matrix;
uniform mat4 projection_matrix;
uniform uint which_polygon;
layout (location = 0) in vec4 t_pos;
layout (location = 1) in vec4 color;
out vec4 vs_fs_color;
vec3 points = vec3(vec2(t_pos),t_pos.w);

float tx = 0.2, ty = -0.5;
mat3x3 translate = mat3x3(1,  0,  0,
                          0,  1,  0,
                          tx, ty, 1);

float theta = radians(270);
mat3x3 rotate = mat3x3( cos(theta), sin(theta), 0,
                       -sin(theta), cos(theta), 0,
                        0,          0,          1);

float scale_x = 0.8, scale_y = 1.2;
mat3x3 scale = mat3x3(scale_x, 0,       0,
                      0,       scale_y, 0,
                      0,       0,       1);

float shear_x = 0.3;
mat3x3 shear = mat3x3(1,       0, 0,
                      shear_x, 1, 0,
                      0,       0, 1);

mat3x3 flipx = mat3x3(-1, 0, 0,
                       0, 1, 0,
                       0, 0, 1);

void main(void)
{
    points = translate * points;
    points = rotate * points;
    points = scale * points;
    points = shear * points;
    points = flipx * points;
    gl_Position = vec4(vec2(points), -1, 1);
    vs_fs_color = color;
}
