#define UNIFORM 1
#define TEXTURE 2
#define CUBEMAP 3

//#define SHADOW 

#ifndef DIFFUSE
#define DIFFUSE TEXTURE
#endif

#ifndef AMBIENT
#define AMBIENT CUBEMAP
#endif

#ifndef SPECULAR
#define SPECULAR CUBEMAP
#endif

#ifndef SPECULAR_POW
#define SPECULAR_POW UNIFORM
#endif

#ifndef TRANSLUCENCY
#define TRANSLUCENCY UNIFORM
#endif

const float Ambient_strength = 1.f;
const float Specular_strength = 0.f;
const float Diffuse_strength = 0.f;

layout(std140) uniform global
{
    mat4    mvp;
    mat4    light_view;
    vec3    light_dir;
    float   scale;
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
uniform float u_SpecularPow = 8.f;
uniform float u_Translucency = 1.f;

uniform sampler2D u_TextureDiffuse;
uniform sampler2D u_TextureAmbient;
uniform sampler2D u_TextureSpecular;
uniform sampler2D u_TextureSpecularPow;
uniform float u_TextureSpecularPow = 8.f;
uniform float u_TextureTranslucency = 1.f;

uniform samplerCube  u_Cubemap;
uniform samplerCube  u_CubemapBlurred;

vec4 get_albedo()
{
#if DIFFUSE == TEXTURE
	return texture(u_TextureDiffuse, vs_out.TexCoord);
#elif DIFFUSE == UNIFORM
	return u_Diffuse;
#else
    return vec4(1);
#endif
}

vec4 get_ambient(vec4 Albedo)
{
#if AMBIENT == UNIFORM
	return u_Ambient * Ambient_strength * Albedo;
#elif AMBIENT == TEXTURE
	return texture(u_TextureAmbient, vs_out.TexCoord) * Albedo;
#elif AMBIENT == CUBEMAP
	return texture(u_CubemapBlurred, vs_out.NormalModelSpace) * Ambient_strength * Albedo;
#endif
}

vec4 get_diffuse(vec4 Albedo)
{
	vec4 Diffuse_power = texture(u_CubemapBlurred, vs_out.NormalModelSpace) * Diffuse_strength;
	return Diffuse_power * Albedo;
}

float   get_translucency()
{
#elif TRANSLUCENCY == TEXTURE
	return texture(u_TextureTranslucency, vs_out.TexCoord)
#elif TRANSLUCENCY == UNIFORM
	return u_Translucency;
#else
    return 1.f;
#endif
}

float   get_specular_power()
{
#elif SPECULAR == TEXTURE
	return texture(u_TextureSpecularPow, vs_out.TexCoord)* spec;
#elif SPECULAR == UNIFORM
	return u_SpecularPow * Specular_strength * length(spec.xyz);
#else
    return 1.f;
#endif
}

vec4 get_specular()
{
    vec3 viewDir = normalize(vs_out.FragPos.xyz);
    vec3 eyeReflectDir = reflect(inverse(mat3(g.mvp)) * viewDir, vs_out.NormalModelSpace); 
    vec4 spec = pow(texture(u_Cubemap, eyeReflectDir), get_specular_power());
#if SPECULAR == TEXTURE
	return texture(u_TextureSpecular, vs_out.TexCoord)* spec;
#elif SPECULAR == UNIFORM
	return u_Specular * Specular_strength * length(spec.xyz);
#elif SPECULAR == CUBEMAP
	return spec * Specular_strength;
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

void main()
{ 
    vec4 Albedo = get_albedo();
    vec4 color = get_specular() + get_diffuse(Albedo) + get_ambient(Albedo);
    color = vec4(pow(color.rgb, vec3(2.2f)), get_translucency()); // ??????
    o_color = color;
}
