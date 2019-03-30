#version 330 core


layout(location = 0)in vec4  Position;
layout(location = 1)in vec2  TexCoord;
layout(location = 2)in vec3  Normal;

out vec3 v_normal;
out vec2 v_uv;

const float M_PI = 3.1415926535897932384626433832795f;
uniform vec2 angles = vec2(0);
uniform vec3 position = vec3(0);
uniform float scale = 0.01f;

void main()
{
	mat4 u_MVP = mat4(
		cos(angles.y), 0.f,	sin(angles.y),	0.f,
		0.f,	1.f,	0.f,	0.f,
		-sin(angles.y),0.f,	cos(angles.y),	0.f,
		0.f,	0.f,	0.f,	1.f
	) * mat4(
		1.f,		0.f,		0.f,		0.f,
		0.f,		cos(angles.x),		-sin(angles.x),	0.f,
		0.f,		sin(angles.x),		cos(angles.x),		0.f,
		0.f,		0.f,		0.f,		1.f
	) * mat4(
		scale,      0.f,	0.f,    0,
		0.f,        scale,	0.f,    0,
		0.f,        0.f,	scale,  0,
		position, 1
	);

	vec4 NewPosition = u_MVP * Position;
	gl_Position = NewPosition;
	v_normal = normalize(u_MVP * vec4(Normal, 0)).xyz;
	v_uv = TexCoord;
}