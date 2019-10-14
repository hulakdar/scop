/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 23:14:52 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/13 23:26:24 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"
#include "scop.h"

void			prepend_define(const char **define, t_shader_code *arrays)
{
	GLuint	length;
	char	*allocated;

	allocated = ft_strdup(*define);
	ft_vec_pushback(&arrays->lines, &allocated);
	length = ft_strlen(*define);
	ft_vec_pushback(&arrays->lengths, &length);
}

t_shader_code	get_shader_source(const char *filepath, t_vector *defines)
{
	const int		fd = open(filepath, O_RDONLY);
	char			*line;
	t_shader_code	source;
	GLuint			length;

	ft_vec_init(&source.lines, sizeof(char *), 32);
	ft_vec_init(&source.lengths, sizeof(GLuint), 32);
	ft_vec_for_each(defines, (t_for_each_predicate)prepend_define, &source);
	while (get_next_line(fd, &line) > 0)
	{
		line = ft_strcat(line, "\n");
		ft_vec_pushback(&source.lines, &line);
		length = ft_strlen(line);
		ft_vec_pushback(&source.lengths, &length);
	}
	return (source);
}

GLint			compile_single_shader(unsigned int type,
										const char *path,
										t_vector *defines)
{
	const int		shader = glCreateShader(type);
	int				result;
	char			*message;
	t_shader_code	source;

	source = get_shader_source(path, defines);
	GLCALL(glShaderSource(shader, source.lines.back,
		(const GLchar *const *)source.lines.data,
		(const GLint *)source.lengths.data));
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
	ft_vec_destruct(&source.lines, free);
	return (shader);
}

GLint			compile_shaders(char *vertex_path,
								char *fragment_path,
								t_vector *defines)
{
	GLCALL(const GLint	program = glCreateProgram());
	GLint		shaders[2];
	GLuint		block_index;

	shaders[0] = compile_single_shader(GL_VERTEX_SHADER, vertex_path, defines);
	shaders[1] = compile_single_shader(GL_FRAGMENT_SHADER,
											fragment_path, defines);
	GLCALL(glAttachShader(program, shaders[0]));
	GLCALL(glAttachShader(program, shaders[1]));
	GLCALL(glLinkProgram(program));
	GLCALL(glValidateProgram(program));
	GLCALL(block_index = glGetUniformBlockIndex(program, "global"));
	if (block_index != GL_INVALID_INDEX)
		GLCALL(glUniformBlockBinding(program, block_index, 0));
	return (program);
}

GLuint			compile_default_shader(char *vert, char *frag)
{
	t_vector	defines;
	GLuint		result;
	const char	*line = "#version 410\n";

	ft_vec_init(&defines, sizeof(char *), 4);
	ft_vec_pushback(&defines, &line);
	result = compile_shaders(vert, frag, &defines);
	ft_vec_del(&defines);
	return (result);
}
