layout(location = 0)in vec4  iPosition;
layout(location = 1)in vec3  iNormal;
layout(location = 2)in vec2  iTexCoord;

layout(std140) uniform global
{
    mat4    mvp;
    vec3    LightDir;
}           g;

out VS_OUT
{
    vec4 FragPos;
    vec2 TexCoord;
    vec3 Normal;
}   vs_out;

void main()
{
    vs_out.FragPos = g.mvp * iPosition;
	gl_Position = vs_out.FragPos;
	vs_out.Normal = normalize(mat3(g.mvp) * iNormal);
	vs_out.TexCoord = iTexCoord;
}
