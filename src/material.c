/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 23:36:24 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/13 23:40:01 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "shaders.h"

void	add_defines(t_vector *defines, t_material *mat)
{
	char *result;

	if (mat->has_texture)
		result = "#define DIFFUSE 2\n";
	else
		result = "#define DIFFUSE 1\n";
	ft_vec_pushback(defines, &result);
}

void	set_uniforms(GLuint result, t_material *mat)
{
	GLint location;

	if (mat->has_texture)
	{
		if ((location = glGetUniformLocation(result, "u_TextureDiffuse")) >= 0)
			GLCALL(glUniform1i(location, 2));
	}
	else
	{
		if ((location = glGetUniformLocation(result, "u_Diffuse")) >= 0)
			GLCALL(glUniform4fv(location, 1, mat->diffuse_color));
	}
}

GLuint	generate_shader(t_material *mat)
{
	t_vector	defines;
	GLuint		result;
	const char	*line = "#version 410\n";

	ft_vec_init(&defines, sizeof(char *), 4);
	ft_vec_pushback(&defines, &line);
	add_defines(&defines, mat);
	result = compile_shaders("res/shaders/uber_vertex.shader",
		"res/shaders/uber_fragment.shader", &defines);
	GLCALL(glUseProgram(result));
	set_uniforms(result, mat);
	ft_vec_del(&defines);
	return (result);
}
