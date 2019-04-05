#include "scop.h"
#include "obj.h"
#include "shaders.h"
#include <stdio.h>
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

static void kick_prepare_model(const char *filepath, t_model *model)
{
	parse_obj(filepath);
	GLCall(glGenBuffers(1, &model->vertex_buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, model->vertex_buffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER, model->vertecies.back *
		model->vertecies.size_of_type, model->vertecies.data, GL_STATIC_DRAW));
	GLCall(glGenVertexArrays(1, &model->vertex_array));
	GLCall(glBindVertexArray(model->vertex_array));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
		(GLvoid *)offsetof(t_vertex, position)));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
		(GLvoid *)offsetof(t_vertex, uv)));
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
		(GLvoid *)offsetof(t_vertex, normal)));
	model->shader_program = compile_shaders("res/shaders/vertex.shader", "res/shaders/fragment.shader");
	GLCall(glUseProgram(model->shader_program));
}

int main(int argc, const char *argv[])
{
	SDL_Window *window;
	t_model model;

	if (argc != 2)
		exit(scop_error("Wrong number of arguments\nShould be:\nscop filename.obj"));
	window = scop_initialize();
	ft_vec_init(&model.vertecies, sizeof(t_vertex), 256);
	ft_vec_init(&model.submeshes, sizeof(t_vertex), 32);
	kick_prepare_model(argv[1], &model);
	return event_loop(window, model);
}