#define UNIFORM 1
#define TEXTURE 2
#define NORMAL 3
#define UV 4

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
    vec3    light_dir;
}           g;

in VS_OUT
{
    vec4 FragPos;
    vec4 FragPosLight;
    vec2 TexCoord;
    vec3 Normal;
}        vs_out;

out vec4 o_color;

uniform vec4 u_Diffuse = vec4(1.9, 1.9, 1.9, 1);
uniform vec4 u_Ambient = vec4(0.4, 0.4, 0.5, 1);
uniform vec4 u_Specular = vec4(1);
const float Ambient_strength = .5f;
const float Specular_strength = .7f;

uniform sampler2D u_TextureD;
uniform sampler2D u_TextureA;
uniform sampler2D u_TextureS;
uniform sampler2D u_Shadow;
uniform sampler2D u_Cubemap;

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

vec4 get_diffuse(float shadow)
{
	float Diffuse_power = max(0, dot(vs_out.Normal, g.light_dir));
    Diffuse_power *= shadow;

#if DIFFUSE == NORMAL
	return vec4(vs_out.Normal,1);
#elif DIFFUSE == TEXTURE
	return texture(u_TextureD, vs_out.TexCoord) * Diffuse_power;
#elif DIFFUSE == UNIFORM
	return u_Diffuse * Diffuse_power;
#elif DIFFUSE == UV
	return vec4(vs_out.TexCoord, 1,1);
#endif
}

vec4 get_specular(float shadow)
{
    vec3 viewDir = normalize(-vs_out.FragPos.xyz);
    vec3 reflectDir = reflect(-g.light_dir, vs_out.Normal); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
#if SPECULAR == NORMAL
	return vec4(vs_out.Normal,1) * spec;
#elif SPECULAR == TEXTURE
	return texture(u_TextureS, vs_out.TexCoord) * Specular_strength * spec;
#elif SPECULAR == UNIFORM
	return u_Specular * Specular_strength * spec;
#endif
}

float shadow()
{
    vec3 ProjectedCoords = vs_out.FragPosLight.xyz / vs_out.FragPosLight.w;
    ProjectedCoords *= 0.5;
    ProjectedCoords += 0.5;
    float ClosestDepth = texture(u_Shadow, ProjectedCoords.xy).r;
    float CurrentDepth = ProjectedCoords.z;
    float bias = max(0.01 * (1.0 - dot(vs_out.Normal, g.light_dir)), 0.001);
    return float(CurrentDepth - bias > ClosestDepth);
}

void main()
{ 
    float shadow_factor = shadow();
    o_color = get_diffuse(shadow_factor) + get_specular(shadow_factor) + get_ambient();
}
