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

static void	setup_texture_sampler(GLenum texture_type, GLuint *texture_id)
{
	GLCALL(glGenTextures(1, texture_id));
	GLCALL(glActiveTexture(GL_TEXTURE0));
	GLCALL(glBindTexture(texture_type, *texture_id));
	GLCALL(glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(texture_type, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCALL(glTexParameteri(texture_type, GL_TEXTURE_WRAP_T, GL_REPEAT));
}

GLuint		get_default_texture(void)
{
	static GLuint default_texture;

	if (default_texture)
		return (default_texture);
	default_texture = create_texture_2d("res/default.png");
	return (default_texture);
}

GLuint		create_texture_cube(const char *folder)
{
	const char *const	faces[] = {"right.jpg", "left.jpg", "top.jpg",
						"bottom.jpg", "front.jpg", "back.jpg"};
	char				*filename;
	SDL_Surface			*local_buffer;
	GLuint				texture_id;
	int					i;

	i = -1;
	setup_texture_sampler(GL_TEXTURE_CUBE_MAP, &texture_id);
	while (++i < 6)
	{
		filename = ft_strcat(ft_strdup(folder), faces[i]);
		local_buffer = IMG_Load(filename);
		free(filename);
		if (!local_buffer)
			exit(scop_error(IMG_GetError()));
		GLCALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
			local_buffer->w, local_buffer->h, 0, GL_BGRA, GL_UNSIGNED_BYTE,
			local_buffer->pixels));
		SDL_FreeSurface(local_buffer);
	}
	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT));
	GLCALL(glGenerateMipmap(GL_TEXTURE_CUBE_MAP));
	return (texture_id);
}

GLuint		create_texture_2d(const char *filename)
{
	SDL_Surface	*local_buffer;
	GLuint		texture_id;

	local_buffer = IMG_Load(filename);
	if (!local_buffer)
		exit(scop_error(IMG_GetError()));
	setup_texture_sampler(GL_TEXTURE_2D, &texture_id);
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, local_buffer->w,
	local_buffer->h, 0, GL_RGB, GL_UNSIGNED_BYTE, local_buffer->pixels));
	SDL_FreeSurface(local_buffer);
	return (texture_id);
}

t_material	get_default_material(void)
{
	t_material result;

	ft_bzero(&result, sizeof(result));
	result.name = ft_strdup("default");
	result.diffuse_tex = get_default_texture();
	result.diffuse_color[0] = 1.f;
	result.diffuse_color[1] = 1.f;
	result.diffuse_color[2] = 1.f;
	result.diffuse_color[3] = 1.f;
	return (result);
}
