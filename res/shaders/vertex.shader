#version 330 core

layout(location = 0)in vec4  Position;
layout(location = 1)in vec2  TexCoord;
layout(location = 2)in vec3  Normal;

out vec3 v_normal;
out vec2 v_uv;

const float M_PI = 3.1415926535897932384626433832795f;
uniform float x = 0.f;
uniform float y = 0.f;
uniform float z = 0.f;


void main()
{
	mat4 u_MVP = mat4(
		cos(y), 0.f,	sin(y),	0.f,
		0.f,	1.f,	0.f,	0.f,
		-sin(y),0.f,	cos(y),	0.f,
		0.f,	0.f,	0.f,	1.f
	) * mat4(
		1.f,		0.f,		0.f,		0.f,
		0.f,		cos(x),		-sin(x),	0.f,
		0.f,		sin(x),		cos(x),		0.f,
		0.f,		0.f,		0.f,		1.f
	) * mat4(
		cos(z),		-sin(z),	0.f, 0.f,
		sin(z),		cos(z),		0.f, 0.f,
		0.f,		0.f,		1.f, 0.f,
		0.f,		0.f,		0.f, 1.f
	) * mat4(
		.1f,	0.f,	0.f, 0.f,
		0.f,	.1f,	0.f, 0.f,
		0.f,	0.f,	.1f, 0.f,
		0.f,	0.f,	0.f, 1.f
	);

	vec4 NewPosition = u_MVP * Position;
	gl_Position = NewPosition;
	v_normal = normalize(u_MVP * vec4(Normal, 0)).xyz;
	v_uv = TexCoord;
}