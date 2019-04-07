layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform vec2 u_angles = vec2(0.f);

void main()
{
	mat3 MVP =mat3(
		1.f,		0.f,		0.f,	
		0.f,		cos(-u_angles.x),		-sin(-u_angles.x),
		0.f,		sin(-u_angles.x),		cos(-u_angles.x)
	) * mat3(
		cos(-u_angles.y), 0.f,	sin(-u_angles.y),
		0.f,	1.f,	0.f,
		-sin(-u_angles.y),0.f,	cos(-u_angles.y)
	);

	TexCoords = aPos * MVP;
	gl_Position = vec4(aPos.xy, 1.f, 1.f);
}
