#include "shaders.h"
#include "scop.h"
#include <malloc.h>

t_shader_source_array get_shader_source(const char *filepath)
{
	const int				fd = open(filepath, O_RDONLY);
	char					*line;
	t_shader_source_array	arrays;
	GLuint					length;

	ft_vec_init(&arrays.lines, sizeof(char *), 32);
	ft_vec_init(&arrays.lengths, sizeof(GLuint), 32);
	while (get_next_line(fd, &line) > 0)
	{
		line = ft_strcat(line, "\n");
		ft_vec_pushback(&arrays.lines, &line);
		length = ft_strlen(line);
		ft_vec_pushback(&arrays.lengths, &length);
	}
	return arrays;
}

GLint compile_single_shader(unsigned int type, const char *path)
{
	const int				shader = glCreateShader(type);
	int						result;
	char					*message;
	t_shader_source_array	source = get_shader_source(path);

	GLCall(glShaderSource(shader, source.lines.back,
		(const GLchar * const *)source.lines.data,
		(const GLuint *)source.lengths.data));
	GLCall(glCompileShader(shader));
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &result);
		message = alloca(result);
		glGetShaderInfoLog(shader, result, &result, message);
		exit(scop_error(message));
		glDeleteShader(shader);
	}
	ft_vec_del(&source.lengths);
	//ft_vec_destruct(&source.lines);
	return shader;
}

GLint compile_shaders(const char *vertex_path, const char *fragment_path)
{
	const GLint				program = glCreateProgram();
	GLint					shaders[2];

	shaders[0] = compile_single_shader(GL_VERTEX_SHADER, vertex_path);
	shaders[1] = compile_single_shader(GL_FRAGMENT_SHADER, fragment_path);
	GLCall(glAttachShader(program, shaders[0]));
	GLCall(glAttachShader(program, shaders[1]));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));
	return program;
}
