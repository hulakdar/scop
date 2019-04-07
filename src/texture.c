#include "scop.h"

static void	setup_texture_sampler(GLenum texture_type)
{
	GLCall(glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(texture_type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(texture_type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
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
	GLCall(glGenTextures(1, &texture_id));
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id));
	while (++i < 6)
	{
		filename = ft_strcat(ft_strdup(folder), faces[i]);
		local_buffer = IMG_Load(filename);
		free(filename);
		if (!local_buffer)
			exit(scop_error(IMG_GetError()));
		GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
			local_buffer->w, local_buffer->h, 0, GL_RGB, GL_UNSIGNED_BYTE,
			local_buffer->pixels));
		SDL_FreeSurface(local_buffer);
	}
	setup_texture_sampler(GL_TEXTURE_CUBE_MAP);
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
	return texture_id;
}

GLuint		create_texture_2d(const char *filename)
{
	SDL_Surface	*local_buffer;
	GLuint		texture_id;

	local_buffer = IMG_Load(filename);
	if (!local_buffer)
		exit(scop_error(IMG_GetError()));
	GLCall(glGenTextures(1, &texture_id));
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture_id));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, local_buffer->w, local_buffer->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer->pixels));
	setup_texture_sampler(GL_TEXTURE_2D);
	SDL_FreeSurface(local_buffer);
	return texture_id;
}
