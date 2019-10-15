#define NONE    0
#define UNIFORM 1
#define TEXTURE 2

#define SHADOW 0

#ifndef DIFFUSE
#define DIFFUSE UNIFORM
#endif

const float Ambient_strength = 0.3;
const float Specular_strength = 0.1;
const float Diffuse_strength = 0.5;

layout(std140) uniform global
{
    mat4    mvp;
    mat4    light_view;
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

const vec3 u_Ambient = vec3(1.0);

#if DIFFUSE == TEXTURE
uniform sampler2D u_TextureDiffuse;
#else
uniform vec4 u_Diffuse = vec4(0.9, 1.9, 1.0, 1);
#endif

uniform samplerCube  u_Cubemap;

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
	return u_Ambient * Ambient_strength * Albedo;
}

vec3 get_diffuse(vec3 Albedo)
{
    float Diffuse_power = max(dot(vs_out.NormalModelSpace, vec3(-0.4, 0.0, -1.0)), 0.0) * Diffuse_strength;
	return Diffuse_power * Albedo;
}

vec3 get_specular()
{
    vec3 viewDir = normalize(vs_out.FragPos.xyz);
    vec3 eyeReflectDir = reflect(inverse(mat3(g.mvp)) * viewDir, vs_out.NormalModelSpace); 
    vec3 spec = texture(u_Cubemap, eyeReflectDir).xyz;
	return spec * Specular_strength;
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
    o_color = vec4(color, 1.0);
}
