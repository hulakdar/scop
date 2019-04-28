layout(location = 0)in vec4  iPosition;
layout(location = 1)in vec3  iNormal;
layout(location = 2)in vec2  iTexCoord;

layout(std140) uniform global
{
    mat4    mvp;
    mat4    light_view;
    vec3    light_dir;
}           g;

out VS_OUT
{
    vec4 FragPos;
    vec4 FragPosLight;
    vec2 TexCoord;
    vec3 Normal;
}   vs_out;

void main()
{
    vs_out.FragPos = g.mvp * iPosition;
    vs_out.FragPosLight = g.light_view * iPosition;
	vs_out.Normal = normalize(mat3(g.mvp) * iNormal);
	vs_out.TexCoord = iTexCoord;
	gl_Position = vs_out.FragPos;
}
