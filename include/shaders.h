#pragma once
#include "libft.h"
#include "GL/glew.h"

typedef struct	s_shader_source_array
{
	t_vector	lines;
	t_vector	lengths;
}				t_shader_source_array;

GLint	compile_shaders(const char *vertex_path, const char *fragment_path, t_vector defines);
GLuint	compile_default_shader();
GLuint	get_skybox_shader();