/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 23:00:59 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/14 00:21:21 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "shaders.h"
#include "stbi_implementation.h"

static void	setup_texture_sampler(GLenum texture_type, GLuint *texture_id)
{
	(glGenTextures(1, texture_id));
	(glActiveTexture(GL_TEXTURE0));
	(glBindTexture(texture_type, *texture_id));
	(glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	(glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	(glTexParameteri(texture_type, GL_TEXTURE_WRAP_S, GL_REPEAT));
	(glTexParameteri(texture_type, GL_TEXTURE_WRAP_T, GL_REPEAT));
}

GLuint		create_texture_cube(const char *folder)
{
	const char		*faces[] = {"right.jpg", "left.jpg", "top.jpg",
						"bottom.jpg", "front.jpg", "back.jpg"};
	char			*filename;
	t_texture_data	data;
	GLuint			texture_id;
	int				i;

	i = -1;
	setup_texture_sampler(GL_TEXTURE_CUBE_MAP, &texture_id);
	while (++i < 6)
	{
		filename = ft_strcat(ft_strdup(folder), faces[i]);
		data.ptr = stbi_load(filename, &data.x, &data.y, NULL, 3);
		free(filename);
		if (!data.ptr)
			exit(scop_error("Unable to load skybox properly."));
		(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
		data.x, data.y, 0, GL_RGB, GL_UNSIGNED_BYTE, data.ptr));
		free(data.ptr);
	}
	(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT));
	(glGenerateMipmap(GL_TEXTURE_CUBE_MAP));
	return (texture_id);
}

GLuint		create_texture_2d(const char *filename)
{
	t_texture_data	data;
	GLuint			texture_id;

	data.ptr = stbi_load(filename, &data.x, &data.y, NULL, 3);
	if (!data.ptr)
		exit(scop_error("Failed to load texture"));
	setup_texture_sampler(GL_TEXTURE_2D, &texture_id);
	(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data.x, data.y,
		0, GL_RGB, GL_UNSIGNED_BYTE, data.ptr));
	free(data.ptr);
	return (texture_id);
}
