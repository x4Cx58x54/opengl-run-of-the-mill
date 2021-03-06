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

void rotate_around_point_xyz(float px, float py, float pz, float rx, float ry, float rz)
{
    translate(-px, -py, -pz);
    rotate_x(rx);
    rotate_y(ry);
    rotate_z(rz);
    translate(px, py, pz);
}

void rotate_around_axis(float x0, float y0, float z0, float x1, float y1, float z1, float theta)
{
    float c = cos(theta);
    float s = sin(theta);
    float x = x1 - x0;
    float y = y1 - y0;
    float z = z1 - z0;
    mat4 rot_axis_mat = mat4(
        x*x+(1-x*x)*c, x*y*(1-c)+z*s, x*z*(1-c)-y*s, 0,
        x*y*(1-c)-z*s, y*y+(1-y*y)*c, y*z*(1-c)+x*s, 0,
        x*z*(1-c)+y*s, y*z*(1-c)-x*s, z*z+(1-z*z)*c, 0,
        0,             0,             0,             1
    );
    translate(-x0, -y0, -z0);
    points = rot_axis_mat * points;
    translate(x0, y0, z0);
}

void main(void)
{
    // initial transform, along with axes.
    rotate_y(20);
    rotate_x(15);
    translate(-0.3, -0.3, 0);

    rotate_around_axis(0.2, 0.3, 0.5, 0.15, 0.45, -0.6, 90);
    translate(0, -1.1, 0.1);
    rotate_x(35);

    gl_Position = points;
    vs_color = in_color;
}
