#define SDL_MAIN_HANDLED
#include "scop.h"
#include "obj.h"
#include "shaders.h"
#include <stdio.h>
#include <signal.h>

static void setup_gl_attrubutes()
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

static SDL_Window *scop_initialize()
{
	SDL_Window *window;
	GLenum Result;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		exit(scop_error("SDL not initialized"));
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		exit(scop_error("SDL_image initialization ERROR"));
	setup_gl_attrubutes();
	window = SDL_CreateWindow("scop", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(window);
	if ((Result = glewInit()) != GLEW_OK)
		exit(scop_error((const char *)glewGetErrorString(Result)));
	GLCALL(glEnable(GL_DEPTH_TEST));
	get_default_texture();
	return window;
}

static void prepare_buffers(t_model *model)
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
	model->skybox_blurred.texture_type = GL_TEXTURE_CUBE_MAP;
	model->skybox_blurred.texture = create_texture_cube("res/skybox_blurred/");
}

int main(int argc, const char *argv[])
{
	SDL_Window	*window;
	t_model		model;
	pthread_t	thread;

	if (argc < 2 || argc > 3)
		exit(scop_error("Wrong number of arguments\n"
			"Should be:\n"
			"scop filename.obj [-b](blocking)\n"));
	model.filepath = argv[1];
	window = scop_initialize();
	ft_vec_init(&model.vertecies, sizeof(t_vertex), 100);
	ft_vec_init(&model.submeshes, sizeof(t_submesh), 1);
	pthread_mutex_init(&model.lock, NULL);
	pthread_create(&thread, NULL, (void *(*)(void *))parse_obj, &model);
	if (argc == 3 && !ft_strcmp(argv[2], "-b"))
		pthread_join(thread, NULL);
	prepare_buffers(&model);
	event_loop(window, &model);
	pthread_kill(thread, SIGTERM);
	pthread_join(thread, NULL);
}