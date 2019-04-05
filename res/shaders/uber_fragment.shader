#define UNIFORM 1
#define TEXTURE 2
#define NORMAL 3

#ifndef COLOR
#define COLOR TEXTURE
#endif

in vec3 Normal;
in vec2 TexCoord;

out vec4 o_color;

uniform vec4 u_Color = vec4(1, 0, 1, 1);
const vec3 light_dir = normalize(vec3(1, 1, -1));
const float Ambient = 0.64f;

uniform sampler2D u_Texture;
void main()
{
	float Diffuse_power = max(0, dot(Normal, light_dir));
    vec4 mask = vec4(Diffuse_power + Ambient);
    mask.w = 1;
#if COLOR == NORMAL
	vec4 diffuse = vec4(Normal,1);
#elif COLOR == TEXTURE
	vec4 diffuse = texture(u_Texture, TexCoord);
#elif COLOR == UNIFORM
	vec4 diffuse = u_Color;
#endif
    o_color = tex_d * mask;
}