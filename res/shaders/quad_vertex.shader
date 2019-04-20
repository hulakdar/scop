
layout(location = 0) in vec2 aPos;

layout(std140) uniform global
{
    mat4    mvp;
    mat4    light_view;
    vec3    LightDir;
}           g;

out VS_OUT
{
    vec2 FragPos;
    vec2 TexCoord;
}   vs_out;

void main()
{
    vs_out.FragPos = aPos;
    vs_out.TexCoord = aPos * 0.5 + 0.5;
	gl_Position = vec4(aPos, 1, 1);
}
