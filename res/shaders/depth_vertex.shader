
layout(location = 0) in vec4 aPos;

layout(std140) uniform global
{
    mat4    mvp;
    mat4    light_view;
    vec3    LightDir;
}           g;

void main()
{
	gl_Position = g.light_view * aPos;
}
