#version 330 core

#define UNIFORM 1
#define TEXTURE 2

#define COLOR TEXTURE

in vec3 v_normal;
in vec2 v_uv;

out vec4 o_color;

uniform vec4 u_Color = vec4(1, 0, 1, 1);
const vec3 light_dir = normalize(vec3(1, 1, -1));
const float Ambient = 0.64f;

uniform sampler2D u_Texture;
void main()
{
	float Diffuse = max(0, dot(v_normal, light_dir));
    vec4 mask = vec4(Diffuse + Ambient);
    mask.w = 1;
#if COLOR == TEXTURE
    vec4 tex_d = texture(u_Texture, v_uv) * mask;
#elif COLOR == UNIFORM
	vec4 tex_d = u_Color;
#else
#error "Define COLOR"
#endif
    o_color = tex_d;
}