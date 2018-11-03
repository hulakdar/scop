#version 330 core

in vec3 v_normal;
in vec2 v_uv;

out vec4 o_color;

uniform vec4 u_Color = vec4(1, 0, 1, 1);
const vec3 light_dir = normalize(vec3(1, 1, -1));
const float Ambient = 0.94f;

uniform sampler2D u_Texture;
void main()
{
	float Diffuse = max(0, dot(v_normal, light_dir));
	o_color = texture(u_Texture, v_uv) * (Diffuse + Ambient);
}