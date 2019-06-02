#define UNIFORM 1
#define TEXTURE 2
#define NORMAL 3
#define UV 4
#define CUBEMAP 5

//#define SHADOW 

#ifndef DIFFUSE
#define DIFFUSE UNIFORM
#endif

#ifndef AMBIENT
#define AMBIENT CUBEMAP
#endif

#ifndef SPECULAR
#define SPECULAR CUBEMAP
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
    vec3 NormalModelSpace;
}        vs_out;

out vec4 o_color;

uniform vec4 u_Diffuse = vec4(1.9, 1.9, 1.9, 1);
uniform vec4 u_Ambient = vec4(0.4, 0.4, 0.5, 1);
uniform vec4 u_Specular = vec4(1);
const float Ambient_strength = .1f;
const float Specular_strength = 0.f;
const float Diffuse_strength = 1.f;

uniform sampler2D u_TextureD;
uniform sampler2D u_TextureA;
uniform sampler2D u_TextureS;
uniform sampler2D u_Shadow;
uniform samplerCube  u_Cubemap;
uniform samplerCube  u_CubemapBlurred;

vec4 get_ambient()
{
#if AMBIENT == NORMAL
	return vec4(vs_out.Normal,1);
#elif AMBIENT == TEXTURE
	return texture(u_TextureA, vs_out.TexCoord) * Ambient_strength;
#elif AMBIENT == UNIFORM
	return u_Ambient * Ambient_strength;
#elif AMBIENT == CUBEMAP
	return texture(u_CubemapBlurred, vs_out.NormalModelSpace) * Ambient_strength;
#endif
}

vec4 get_diffuse(float shadow)
{
	float Diffuse_power = max(0, dot(vs_out.Normal, -g.light_dir)) * Diffuse_strength;
    Diffuse_power *= shadow;

#if DIFFUSE == NORMAL
	return vec4(vs_out.NormalModelSpace,1);
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
    vec4 viewDir = vec4(normalize(-vs_out.FragPos));
    vec3 reflectDir = reflect(-g.light_dir, vs_out.Normal); 
    vec4 eyeReflectDir = reflect(viewDir * inverse(g.mvp), vec4(vs_out.NormalModelSpace, 1)); 
    //float spec = pow(max(dot(viewDir.xyz, reflectDir), 0.0), 16);
#if SPECULAR == NORMAL
	return vec4(vs_out.Normal,1) * spec;
#elif SPECULAR == TEXTURE
	return texture(u_TextureS, vs_out.TexCoord) * Specular_strength * spec;
#elif SPECULAR == UNIFORM
	return u_Specular * Specular_strength * spec;
#elif SPECULAR == CUBEMAP
	return texture(u_Cubemap, eyeReflectDir.xyz) * Specular_strength;
#endif
}

float shadow()
{
    vec3 ProjectedCoords = vs_out.FragPosLight.xyz / vs_out.FragPosLight.w;
    ProjectedCoords *= 0.5;
    ProjectedCoords += 0.5;
    float ClosestDepth = texture(u_Shadow, ProjectedCoords.xy).r;
    float CurrentDepth = ProjectedCoords.z;
    float bias = 0.01; //max(0.01 * (1.0 - dot(vs_out.Normal, g.light_dir)), 0.001);
    return float(CurrentDepth - bias > ClosestDepth);
}

vec4 fresnel(vec4 a, vec4 b)
{
    vec3 viewDir = normalize(vs_out.FragPos.xyz);
    vec3 normal = normalize(vs_out.Normal);
    float alpha = dot(viewDir, normal);

    return mix(a,b,alpha);
}

void main()
{ 
#ifdef SHADOW
    float shadow_factor = shadow();
#else
    const float shadow_factor = 1.f;
#endif
    vec4 color = get_diffuse(shadow_factor) + get_specular(shadow_factor) + get_ambient();
    //color = vec4(pow(color.rgb, vec3(2.2f)), color.w);
    //vec4 color = fresnel(get_diffuse(shadow_factor), get_specular(shadow_factor)) + get_ambient();
    o_color = color;
}
