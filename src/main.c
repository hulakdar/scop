/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 23:25:29 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/13 23:44:53 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "obj.h"
#include "shaders.h"
#include "stb_image.h"
#include <stdio.h>
#include <signal.h>

static void		setup_gl_attrubutes(void)
{
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	SDL_GL_SetSwapInterval(1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, CONTEXT_FLAGS);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, CONTEXT_PROFILE);
}

static void		prepare_buffers(t_model *model)
{
	GLCALL(glGenVertexArrays(1, &model->buffers.vertex_array));
	GLCALL(glGenBuffers(1, &model->buffers.vertex_buffer));
	bind_buffers(model->buffers);
	GLCALL(glEnableVertexAttribArray(0));
	GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
		(GLvoid *)0));
	GLCALL(glEnableVertexAttribArray(1));
	GLCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
		(GLvoid *)offsetof(t_vertex, normal)));
	GLCALL(glEnableVertexAttribArray(2));
	GLCALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
		(GLvoid *)offsetof(t_vertex, uv)));
	model->skybox.shader = get_skybox_shader();
	model->skybox.texture_type = GL_TEXTURE_CUBE_MAP;
	model->skybox.texture = create_texture_cube("res/skybox/");
	stbi_set_flip_vertically_on_load(true);
}

static void		scop_initialize(t_model *model)
{
	GLenum		result;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		exit(scop_error("SDL not initialized"));
	setup_gl_attrubutes();
	model->window = SDL_CreateWindow("scop", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_OPENGL);
	model->context = SDL_GL_CreateContext(model->window);
	if ((result = glewInit()) != GLEW_OK)
		exit(scop_error((const char *)glewGetErrorString(result)));
	GLCALL(glEnable(GL_DEPTH_TEST));
	GLCALL(glEnable(GL_POINT_SIZE));
	glPointSize(8.0f);
	GLCALL(glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS));
	prepare_buffers(model);
}

int				main(int argc, const char *argv[])
{
	t_model		model;
	pthread_t	thread;

	if (argc < 2 || argc > 3)
		exit(scop_error("Wrong number of arguments\n"
			"Should be:\n"
			"scop filename.obj [-b](blocking)\n"));
	ft_bzero(&model, sizeof(model));
	model.filepath = argv[1];
	scop_initialize(&model);
	ft_vec_init(&model.materials, sizeof(t_material), 2);
	ft_vec_init(&model.vertecies, sizeof(t_vertex), 1000);
	ft_vec_init(&model.submeshes, sizeof(t_submesh), 1);
	pthread_mutex_init(&model.lock, NULL);
	pthread_create(&thread, NULL, (void *(*)(void *))parse_obj, &model);
	if (argc == 3 && !ft_strcmp(argv[2], "-b"))
		pthread_join(thread, NULL);
	event_loop(model.window, &model);
	model.request_exit = 1;
	pthread_join(thread, NULL);
	ft_vec_del(&model.submeshes);
	ft_vec_del(&model.vertecies);
	ft_vec_del(&model.materials);
}
