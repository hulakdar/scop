#define UNIFORM 1
#define TEXTURE 2
#define CUBEMAP 3

#define SHADOW 0

#ifndef DIFFUSE
#define DIFFUSE UNIFORM
#endif

#ifndef AMBIENT
#define AMBIENT UNIFORM
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

const float Ambient_strength = 0.0;
const float Specular_strength = 0.0;
const float Diffuse_strength = 1.0;

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

uniform vec4 u_Diffuse = vec4(0.9, 1.9, 1.0, 1);
uniform vec4 u_Ambient = vec4(0.4, 0.4, 0.5, 1);
uniform vec4 u_Specular = vec4(1);
uniform float u_SpecularPow = 8.f;
uniform float u_Translucency = 1.f;

uniform sampler2D u_TextureDiffuse;
uniform sampler2D u_TextureAmbient;
uniform sampler2D u_TextureSpecular;
uniform sampler2D u_TextureSpecularPow;

uniform samplerCube  u_Cubemap;
uniform samplerCube  u_CubemapBlurred;

vec3 get_albedo()
{
#if DIFFUSE == TEXTURE
	return texture(u_TextureDiffuse, vs_out.TexCoord).xyz;
#elif DIFFUSE == UNIFORM
	return u_Diffuse.xyz;
#else
    return vec3(1);
#endif
}

vec3 get_ambient(vec3 Albedo)
{
#if AMBIENT == UNIFORM
	return u_Ambient.xyz * Ambient_strength * Albedo;
#elif AMBIENT == TEXTURE
	return texture(u_TextureAmbient, vs_out.TexCoord).xyz * Albedo;
#elif AMBIENT == CUBEMAP
	return texture(u_CubemapBlurred, vs_out.NormalModelSpace).xyz * Ambient_strength * Albedo;
#endif
}

vec3 get_diffuse(vec3 Albedo)
{
	//vec3 Diffuse_power = texture(u_CubemapBlurred, vs_out.NormalModelSpace).xyz * Diffuse_strength;
    float Diffuse_power = max(dot(vs_out.NormalModelSpace, vec3(0.2)), 0.0);
	return vs_out.NormalModelSpace;
}

float   get_translucency()
{
#if TRANSLUCENCY == TEXTURE
	return texture(u_TextureTranslucency, vs_out.TexCoord)
#elif TRANSLUCENCY == UNIFORM
	return u_Translucency;
#else
    return 1.0;
#endif
}

float   get_specular_power()
{
#if SPECULAR == TEXTURE
	return texture(u_TextureSpecularPow, vs_out.TexCoord)* spec;
#elif SPECULAR == UNIFORM
	return u_SpecularPow * Specular_strength * length(spec.xyz);
#else
    return 1.0;
#endif
}

vec3 get_specular()
{
    vec3 viewDir = normalize(vs_out.FragPos.xyz);
    vec3 eyeReflectDir = reflect(inverse(mat3(g.mvp)) * viewDir, vs_out.NormalModelSpace); 
    vec3 spec = pow(texture(u_Cubemap, eyeReflectDir).xyz, vec3(get_specular_power()));
#if SPECULAR == TEXTURE
	return texture(u_TextureSpecular, vs_out.TexCoord).xyz * spec;
#elif SPECULAR == UNIFORM
	return u_Specular.xyz * Specular_strength * length(spec);
#elif SPECULAR == CUBEMAP
	return spec * Specular_strength;
#endif
}

#if SHADOW
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
#endif

void main()
{ 
    vec3 Albedo = get_albedo();
    vec3 color = get_specular() + get_diffuse(Albedo) + get_ambient(Albedo);
    o_color = vec4(vs_out.NormalModelSpace, get_translucency());
}
