#version 330 core
in vec4 color;
out vec4 fColor;
uniform uint render_type;
vec3 hsvtorgb(in vec3 hsv)
{
    vec3 rgb = clamp(abs(mod(hsv.x*6.0+vec3(0.0,4.0,2.0),6.0)-3.0)-1.0, 0.0, 1.0);
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return hsv.z * mix(vec3(1.0), rgb, hsv.y);
}
float rand(vec2 co){
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}
void main()
{
    float dbpi = 2*acos(-1);
    vec2 curCoord = vec2((gl_FragCoord.x-400)/800, (gl_FragCoord.y-400)/800);
    float curR = sqrt(curCoord.x * curCoord.x + curCoord.y * curCoord.y);
    vec2 raxis = vec2(0.866, 0.5);
    vec2 gaxis = vec2(-0.866, 0.5);
    vec2 baxis = vec2(0, -1);
    float angle = atan(curCoord.y, curCoord.x); // radian
    vec3 angletorgb = vec3(dot(curCoord, raxis)/curR, dot(curCoord, gaxis)/curR, dot(curCoord, baxis)/curR);
    switch(render_type)
    {
    case 0:
        fColor = color;
        break;
    case 1:
        fColor = cos(color);
        break;
    case 2:
        fColor = vec4(angletorgb, 1);
        break;
    case 3:
        fColor = vec4(hsvtorgb(vec3(angle/dbpi, tanh(curR*8), 1)), 1);
        break;
    case 4:
        fColor = cos(0.5*gl_FragCoord) - sin(0.5*gl_FragCoord) +
                     4*vec4(rand(curCoord*31)-0.5, rand(curCoord*67)-0.5, rand(curCoord*53)-0.5, 1);
        break;
    case 5:
        int width = 10;
        fColor = vec4(hsvtorgb(vec3(int(gl_FragCoord.x*421) % width / float(width), 1, 1)), 1)/2 +
                 vec4(hsvtorgb(vec3(int(gl_FragCoord.y*421) % width / float(width), 1, 1)), 1)/2;
        break;
    case 6:
        fColor = vec4(rand(curCoord*157), rand(curCoord*23), rand(curCoord*251), 1);
        break;
    }
}
