#define UNIFORM 1
#define TEXTURE 2
#define NORMAL 3

#ifndef DIFFUSE
#define DIFFUSE UNIFORM
#endif

#ifndef AMBIENT
#define AMBIENT UNIFORM
#endif

#ifndef SPECULAR
#define SPECULAR UNIFORM
#endif

layout(std140) uniform global
{
    mat4    mvp;
    mat4    light_view;
    vec3    LightDir;
}           g;

in VS_OUT
{
    vec4 FragPos;
    vec2 TexCoord;
    vec3 Normal;
}        vs_out;

out vec4 o_color;

uniform vec4 u_Diffuse = vec4(0.9, 0.9, .9, 1);
uniform vec4 u_Ambient = vec4(0.4, 0.4, 0.5, 1);
uniform vec4 u_Specular = vec4(1);
const float Ambient_strength = .5f;
const float Specular_strength = .7f;

uniform sampler2D u_TextureD;
uniform sampler2D u_TextureA;
uniform sampler2D u_TextureS;

vec4 get_diffuse()
{
	float Diffuse_power = max(0, dot(vs_out.Normal, g.LightDir));

#if DIFFUSE == NORMAL
	return vec4(vs_out.Normal,1);
#elif DIFFUSE == TEXTURE
	return texture(u_TextureD, vs_out.TexCoord) * Diffuse_power;
#elif DIFFUSE == UNIFORM
	return u_Diffuse * Diffuse_power;
#endif
}

vec4 get_ambient()
{
#if AMBIENT == NORMAL
	return vec4(vs_out.Normal,1);
#elif AMBIENT == TEXTURE
	return texture(u_TextureA, vs_out.TexCoord) * Ambient_strength;
#elif AMBIENT == UNIFORM
	return u_Ambient * Ambient_strength;
#endif
}

vec4 get_specular()
{
    vec3 viewDir = normalize(-vs_out.FragPos.xyz);
    vec3 reflectDir = reflect(-g.LightDir, vs_out.Normal); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
#if SPECULAR == NORMAL
	return vec4(vs_out.Normal,1) * spec;
#elif SPECULAR == TEXTURE
	return texture(u_TextureS, vs_out.TexCoord) * Specular_strength * spec;
#elif SPECULAR == UNIFORM
	return u_Specular * Specular_strength * spec;
#endif
}

void main()
{ 
    o_color = get_diffuse() + get_ambient() + get_specular();
}
