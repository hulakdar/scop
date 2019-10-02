layout(location = 0) in vec2 aPos;

out vec3 TexCoords;

layout(std140) uniform global
{
    mat4    mvp;
    float   scale;
}           g;

void main()
{
	TexCoords = vec3(aPos, 1) * mat3(g.mvp);
	gl_Position = vec4(aPos, 0.99f, 1.f);
}
