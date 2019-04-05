
layout(location = 0)in vec3  iPosition;
layout(location = 1)in vec2  iTexCoord;
layout(location = 2)in vec3  iNormal;

out vec3 Normal;
out vec2 TexCoord;

const float M_PI = 3.1415926535897932384626433832795f;
uniform vec2 u_angles = vec2(0);
uniform vec3 u_position = vec3(0);
uniform float u_scale = 0.01f;

void main()
{
	mat3 u_MVP =mat3(
		cos(u_angles.y), 0.f,	sin(u_angles.y),
		0.f,	1.f,	0.f,
		-sin(u_angles.y),0.f,	cos(u_angles.y)
	) * mat3(
		1.f,		0.f,		0.f,	
		0.f,		cos(u_angles.x),		-sin(u_angles.x),
		0.f,		sin(u_angles.x),		cos(u_angles.x)
	);

	vec3 NewPosition = u_MVP * iPosition * u_scale + u_position;
	gl_Position = vec4(NewPosition, 1.f);
	Normal = u_MVP * iNormal;
	TexCoord = iTexCoord;
}
