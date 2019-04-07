#define UNIFORM 1
#define TEXTURE 2
#define NORMAL 3

#ifndef DIFFUSE
#define DIFFUSE NORMAL
#endif

#ifndef AMBIENT
#define AMBIENT UNIFORM
#endif

#ifndef SPECULAR
#define SPECULAR UNIFORM
#endif

in vec4 FragPos;
in vec2 TexCoord;
in vec3 Normal;

out vec4 o_color;

uniform vec4 u_Diffuse = vec4(1, 0, 1, 1);
uniform vec4 u_Ambient = vec4(0, 0, 1, 1);
uniform vec4 u_Specular = vec4(1);
const vec3 light_dir = normalize(vec3(1, 1, -1));
const float Ambient_strength = 0.f;
const float Specular_strength = 0.f;

uniform sampler2D u_TextureD;
uniform sampler2D u_TextureA;
uniform sampler2D u_TextureS;

vec4 get_diffuse()
{
	float Diffuse_power = max(0, dot(Normal, light_dir));

#if DIFFUSE == NORMAL
	return vec4(Normal,1);
#elif DIFFUSE == TEXTURE
	return texture(u_TextureD, TexCoord) * Diffuse_power;
#elif DIFFUSE == UNIFORM
	return u_Diffuse * Diffuse_power;
#endif
}

vec4 get_ambient()
{
#if AMBIENT == NORMAL
	return vec4(Normal,1);
#elif AMBIENT == TEXTURE
	return texture(u_TextureA, TexCoord) * Ambient_strength;
#elif AMBIENT == UNIFORM
	return u_Ambient * Ambient_strength;
#endif
}

vec4 get_specular()
{
    vec3 viewDir = normalize(FragPos.xyz);
    vec3 reflectDir = reflect(-light_dir, Normal); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
#if SPECULAR == NORMAL
	return vec4(Normal,1) * spec;
#elif SPECULAR == TEXTURE
	return texture(u_TextureS, TexCoord) * Specular_strength * spec;
#elif SPECULAR == UNIFORM
	return u_Specular * Specular_strength * spec;
#endif
}

void main()
{ 
    o_color = get_diffuse() + get_ambient() + get_specular();
}
