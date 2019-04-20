#include "shaders.h"
#include "scop.h"
#include <malloc.h>

void prepend_define(const char **define, t_shader_source_array *arrays)
{
	GLuint	length;
	char	*allocated;

	allocated = ft_strdup(*define);
	ft_vec_pushback(&arrays->lines, &allocated);
	length = ft_strlen(*define);
	ft_vec_pushback(&arrays->lengths, &length);
}

t_shader_source_array get_shader_source(const char *filepath, t_vector defines)
{
	const int				fd = open(filepath, O_RDONLY);
	char					*line;
	t_shader_source_array	source;
	GLuint					length;

	ft_vec_init(&source.lines, sizeof(char *), 32);
	ft_vec_init(&source.lengths, sizeof(GLuint), 32);
	ft_vec_for_each(&defines, prepend_define, &source);
	while (get_next_line(fd, &line) > 0)
	{
		line = ft_strcat(line, "\n");
		ft_vec_pushback(&source.lines, &line);
		length = ft_strlen(line);
		ft_vec_pushback(&source.lengths, &length);
	}
	return source;
}

GLint compile_single_shader(unsigned int type, const char *path, t_vector defines)
{
	const int				shader = glCreateShader(type);
	int						result;
	char					*message;
	t_shader_source_array	source = get_shader_source(path, defines);

	GLCALL(glShaderSource(shader, source.lines.back,
		(const GLchar * const *)source.lines.data,
		(const GLuint *)source.lengths.data));
	GLCALL(glCompileShader(shader));
	GLCALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &result);
		message = alloca(result);
		glGetShaderInfoLog(shader, result, &result, message);
		exit(scop_error(message));
	}
	ft_vec_del(&source.lengths);
	//ft_vec_destruct(&source.lines);
	return shader;
}

GLint compile_shaders(const char *vertex_path, const char *fragment_path, t_vector defines)
{
	const GLint	program = glCreateProgram();
	GLint		shaders[2];
	GLuint		block_index;

	shaders[0] = compile_single_shader(GL_VERTEX_SHADER, vertex_path, defines);
	shaders[1] = compile_single_shader(GL_FRAGMENT_SHADER, fragment_path, defines);
	GLCALL(glAttachShader(program, shaders[0]));
	GLCALL(glAttachShader(program, shaders[1]));
	GLCALL(glLinkProgram(program));
	GLCALL(glValidateProgram(program));
	GLCALL(block_index = glGetUniformBlockIndex(program, "global"));
	if (block_index != GL_INVALID_INDEX)
		GLCALL(glUniformBlockBinding(program, block_index, 0));
	return program;
}

GLuint compile_default_shader(const char *vert, const char *frag)
{
	t_vector	defines;
	char		*line;
	GLuint		result;

	ft_vec_init(&defines, sizeof(char *), 4);
	line = "#version 410\n";
	ft_vec_pushback(&defines, &line);
	result = compile_shaders(vert, frag, defines);
	ft_vec_del(&defines);
	return result;
}
