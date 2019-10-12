
#include "scop.h"
#include "shaders.h"

void add_defines(t_vector* defines, t_uniform mat, t_attribute attrib)
{
	const char* preface = "#define ";
	const char* define[] = { "DIFFUSE", "AMBIENT",
		"SPECULAR", "SPECULAR_POW", "TRANSLUCENCY" };
	const char* value[] = { "=0", "=1", "=2", "=1" };
	char* result;

	if (mat.type == UT_NONE)
		return;
	result = ft_strdup(preface);
	ft_strcat(result, define[attrib]);
	ft_strcat(result, value[mat.type]);
	ft_vec_pushback(defines, &result);
}

void set_uniforms(GLuint result, t_uniform mat, t_attribute attrib)
{
	const char* uniforms[] = { "u_Diffuse", "u_Ambient", "u_Specular", "u_SpecularPow", "u_Translucency",
		"u_TextureDiffuse", "u_TextureAmbient", "u_TextureSpecular", "u_TextureSpecularPow", "u_TextureTranslucency", };
	GLint location;

	if (mat.type == UT_VEC4)
		if ((location = glGetUniformLocation(result, uniforms[attrib])) >= 0)
			glUniform4fv(location,1, &mat.data.vec4);
	if (mat.type == UT_FLOAT)
		if ((location = glGetUniformLocation(result, uniforms[attrib])) >= 0)
			glUniform1f(location, mat.data.vec1);
	if (mat.type == UT_SAMPLER2D)
		if ((location = glGetUniformLocation(result, uniforms[attrib + 5])) >= 0)
			glUniform1ui(location, mat.data.uint);
}

GLuint generate_shader(t_material *mat)
{
	t_vector	defines;
	GLuint		result;
	const char	*line = "#version 410\n";

	ft_vec_init(&defines, sizeof(char *), 4);
	ft_vec_pushback(&defines, &line);
	add_defines(&defines, mat->diffuse, A_DIFFUSE);
	result = compile_shaders( "res/shaders/uber_vertex.shader",
		"res/shaders/uber_fragment.shader", defines);
	set_uniforms(result, mat->diffuse, A_DIFFUSE);
	ft_vec_destruct(&defines, free);
	return result;
}
