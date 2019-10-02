#include "scop.h"
#include "shaders.h"


static void	setup_texture_sampler(GLenum texture_type)
{
	GLCALL(glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(texture_type, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCALL(glTexParameteri(texture_type, GL_TEXTURE_WRAP_T, GL_REPEAT));
}

GLuint	get_default_texture()
{
	static GLuint default_texture;

	if (default_texture)
		return default_texture;
	default_texture = create_texture_2d("res/default.png");
	return default_texture;
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
	GLCALL(glGenTextures(1, &texture_id));
	GLCALL(glActiveTexture(GL_TEXTURE0));
	GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id));
	while (++i < 6)
	{
		filename = ft_strcat(ft_strdup(folder), faces[i]);
		local_buffer = IMG_Load(filename);
		free(filename);
		if (!local_buffer)
			exit(scop_error(IMG_GetError()));
		GLCALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
			local_buffer->w, local_buffer->h, 0, GL_RGB, GL_UNSIGNED_BYTE,
			local_buffer->pixels));
		SDL_FreeSurface(local_buffer);
	}
	setup_texture_sampler(GL_TEXTURE_CUBE_MAP);
	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT));
	GLCALL(glGenerateMipmap(GL_TEXTURE_CUBE_MAP));
	return texture_id;
}

GLuint		create_texture_2d(const char *filename)
{
	SDL_Surface	*local_buffer;
	GLuint		texture_id;

	local_buffer = IMG_Load(filename);
	if (!local_buffer)
		exit(scop_error(IMG_GetError()));
	GLCALL(glGenTextures(1, &texture_id));
	GLCALL(glActiveTexture(GL_TEXTURE0));
	GLCALL(glBindTexture(GL_TEXTURE_2D, texture_id));
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, local_buffer->w, local_buffer->h, 0, GL_RGB, GL_UNSIGNED_BYTE, local_buffer->pixels));
	setup_texture_sampler(GL_TEXTURE_2D);
	SDL_FreeSurface(local_buffer);
	return texture_id;
}
