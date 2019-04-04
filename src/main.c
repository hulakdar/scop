#include "scop.h"
#include "obj.h"
#include "shaders.h"
#include <stdio.h>
#undef main

SDL_Window *scop_initialize()
{
	const int win_width = 800;
	const int win_height = 800;
	SDL_Window *window;
	GLenum Result;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		exit(scop_error("SDL not initialized"));
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		exit(scop_error("SDL_image initialization ERROR"));
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
	window = SDL_CreateWindow("scop", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(window);
	Result = glewInit();
	if (Result != GLEW_OK)
		exit(scop_error((const char *)glewGetErrorString(Result)));
	GLCall(glEnable(GL_DEPTH_TEST));
	return window;
}

t_model prepare_model(const char *filepath)
{
	t_model model;

	model = parse_obj(filepath);
	GLCall(glGenBuffers(1, &model.vertex_buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, model.vertex_buffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER, model.vertecies.back *
		model.vertecies.size_of_type, model.vertecies.data, GL_STATIC_DRAW));
	GLCall(glGenVertexArrays(1, &model.vertex_array));
	GLCall(glBindVertexArray(model.vertex_array));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
		(GLvoid *)offsetof(t_vertex, position)));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
		(GLvoid *)offsetof(t_vertex, uv)));
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
		(GLvoid *)offsetof(t_vertex, normal)));
	GLCall(glGenTextures(1, &model.texture));
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, model.texture));
	model.shader_program = compile_shaders("res/shaders/vertex.shader", "res/shaders/fragment.shader");
	GLCall(glUseProgram(model.shader_program));
	return model;
}


int main(int argc, const char *argv[])
{
	SDL_Window *window;
	t_model model;
	SDL_Surface *local_buffer;

	if (argc > 2 || argc == 1)
		exit(scop_error("wrong number of arguments"));
	window = scop_initialize();
	model = prepare_model(argv[1]);
	local_buffer = IMG_Load("res/sample.png");
	if (!local_buffer)
		exit(scop_error(IMG_GetError()));
	int tex_sampler_location = glGetUniformLocation(model.shader_program, "u_Texture");
	GLCall(glUniform1i(tex_sampler_location, 0));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, local_buffer->w, local_buffer->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer->pixels));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	SDL_FreeSurface(local_buffer);
	return event_loop(window, model);
}