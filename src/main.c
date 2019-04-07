#include "scop.h"
#include "obj.h"
#include "shaders.h"
#include <stdio.h>
#include <signal.h>
#undef main

static void setup_gl_attrubutes()
{
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
	SDL_GL_SetSwapInterval(1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, CONTEXT_FLAGS);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, CONTEXT_PROFILE);
}

static SDL_Window *scop_initialize()
{
	const int win_width = 800;
	const int win_height = 800;
	SDL_Window *window;
	GLenum Result;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		exit(scop_error("SDL not initialized"));
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		exit(scop_error("SDL_image initialization ERROR"));
	setup_gl_attrubutes();
	window = SDL_CreateWindow("scop", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(window);
	if ((Result = glewInit()) != GLEW_OK)
		exit(scop_error((const char *)glewGetErrorString(Result)));
	GLCall(glEnable(GL_DEPTH_TEST));
	return window;
}

static void prepare_buffers(t_model *model)
{
	GLCall(glGenVertexArrays(1, &model->buffers.vertex_array));
	GLCall(glGenBuffers(1, &model->buffers.vertex_buffer));
	bind_buffers(model->buffers);
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
		(GLvoid *)offsetof(t_vertex, position)));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
		(GLvoid *)offsetof(t_vertex, normal)));
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
		(GLvoid *)offsetof(t_vertex, uv)));
	model->skybox.shader = get_skybox_shader();
	model->skybox.buffers = create_skybox_data();
	model->skybox.texture = create_texture_cube("res/skybox/");
}

int main(int argc, const char *argv[])
{
	SDL_Window *window;
	t_model		model;
	pthread_t	thread;

	if (argc != 2)
		exit(scop_error("Wrong number of arguments\nShould be:\nscop filename.obj"));
	model.filepath = argv[1];
	window = scop_initialize();
	ft_vec_init(&model.vertecies, sizeof(t_vertex), 256);
	ft_vec_init(&model.submeshes, sizeof(t_submesh), 32);
	pthread_mutex_init(&model.lock, NULL);
	pthread_create(&thread, NULL, parse_obj, &model);
	prepare_buffers(&model);
	event_loop(window, &model);
	pthread_kill(thread, SIGTERM);
	pthread_join(thread, NULL);
}