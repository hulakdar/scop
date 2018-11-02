#include "scop.h"
#include "obj.h"
#include <stdio.h>
#undef main

#define GLCall(x) \
	GLClearError();\
	x;\
	SDL_assert(GLCheckError(#x, __FILE__, __LINE__))

#define CUBE 1

void GLClearError()
{
	while (glGetError());
}

char GLCheckError(const char *Function, const char *File, int Line)
{
	GLenum Error;
	while (Error = glGetError())
	{
		__debugbreak();
	}
	return 1;
}

typedef struct	s_shader_source_array
{
	t_vector	lines;
	t_vector	lengths;
}				t_shader_source_array;

t_shader_source_array get_shader_source(const char *filepath)
{
	const int				fd = open(filepath, O_RDONLY);
	char					*line;
	t_shader_source_array	arrays;
	int						length;

	ft_vec_init(&arrays.lines, sizeof(char *), 32);
	ft_vec_init(&arrays.lengths, sizeof(GLint), 32);
	while (get_next_line(fd, &line))
	{
		line = ft_strcat(line, "\n");
		ft_vec_pushback(&arrays.lines, &line);
		length = ft_strlen(line);
		ft_vec_pushback(&arrays.lengths, &length);
	}
	return arrays;
}

GLint compile_single_shader(unsigned int type, const char *path)
{
	const int				shader = glCreateShader(type);
	int						result;
	char					*message;
	t_shader_source_array	source = get_shader_source(path);

	GLCall(glShaderSource(shader, source.lines.back,
		source.lines.data, source.lengths.data));
	GLCall(glCompileShader(shader));
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &result);
		message = alloca(result);
		glGetShaderInfoLog(shader, result, &result, message);
		exit(scop_error(message));
		glDeleteShader(shader);
	}
	//ft_vec_del(&source.lengths);
	//ft_vec_destruct(&source.lines);
	return shader;
}

GLint compile_shaders(const char *vertex_path, const char *fragment_path)
{
	const GLint				program = glCreateProgram();
	GLint					shaders[2];

	shaders[0] = compile_single_shader(GL_VERTEX_SHADER, vertex_path);
	shaders[1] = compile_single_shader(GL_FRAGMENT_SHADER, fragment_path);
	GLCall(glAttachShader(program, shaders[0]));
	GLCall(glAttachShader(program, shaders[1]));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));
	return program;
}

inline static char WindowShouldClose(const SDL_Event* e)
{
	return ( e->type == SDL_QUIT
		|| (e->type == SDL_WINDOWEVENT && e->window.event == SDL_WINDOWEVENT_CLOSE)
		|| (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE) );
}

char scop_error(const char *error)
{
	ft_putstr_fd(error, 2);
#if  _WIN32 || _WIN64
	__debugbreak();
#endif 
	return -1;
}

int main(int argc, const char *argv[])
{
	if (argc > 2 || argc == 1)
		exit(-1);
	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		exit(scop_error("SDL not initialized"));

	//if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	//	exit(scop_error("SDL_image initialization ERROR"));

	SDL_GL_SetSwapInterval(1);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	int WinWidth = 500, WinHeight = 500;

	SDL_Window *Window = SDL_CreateWindow(
		"SDL Test", // Window name
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // position
		WinWidth, WinHeight, // width, height
		SDL_WINDOW_OPENGL // flags
	);

	const float cube[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f
	};

	// creating an opengl context
	SDL_GLContext SdlGlContext = SDL_GL_CreateContext(Window);
	GLenum Result = glewInit();
	if (Result != GLEW_OK)
		exit(scop_error(glewGetErrorString(Result)));

	GLCall(glEnable(GL_DEPTH_TEST));
	//GLCall(glEnable(GL_BLEND));
	//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	char ShouldClose = 0;

#if !CUBE
	t_model model = parse_obj(argv[1]);
#endif

	GLint vertex_buffer;
	GLCall(glGenBuffers(1, &vertex_buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer));
#if CUBE
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW));
#else
	GLCall(glBufferData(GL_ARRAY_BUFFER, model.vertecies.back * model.vertecies.size_of_type, model.vertecies.data, GL_STATIC_DRAW));
#endif

	GLint vertex_array;
	GLCall(glGenVertexArrays(1, &vertex_array));
	GLCall(glBindVertexArray(vertex_array));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex), offsetof(t_vertex, position)));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(t_vertex), offsetof(t_vertex, uv)));
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex), offsetof(t_vertex, normale)));


	GLint shader_program = compile_shaders("res/shaders/vertex.shader", "res/shaders/fragment.shader");
	GLCall(glUseProgram(shader_program));

	
	int x_u_location = glGetUniformLocation(shader_program, "x");
	int y_u_location = glGetUniformLocation(shader_program, "y");
	int z_u_location = glGetUniformLocation(shader_program, "z");



	SDL_Surface *local_buffer = IMG_Load("res\\sample.png");
	if (!local_buffer)
		exit(scop_error(IMG_GetError()));

	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	int tex_sampler_location = glGetUniformLocation(shader_program, "u_Texture");
	glUniform1i(tex_sampler_location, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, local_buffer->w, local_buffer->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

#if !CUBE
	for (int i = 0; i < model.vertecies.back; ++i)
	{
		t_vertex vert = *(t_vertex *)ft_vec_get(&model.vertecies, i);
		printf("vert #%d \n", i);
		printf("%f %f %f\n", vert.position.x, vert.position.y, vert.position.z);
#if WITH_SHIT
		printf("%f %f\n", vert.uv.x, vert.uv.y);
		printf("%f %f %f\n", vert.normale.x, vert.normale.y, vert.normale.z);
#endif
	}
#endif

	SDL_Event	e;
	while (!ShouldClose)
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		while (SDL_PollEvent(&e))
			ShouldClose = WindowShouldClose(&e);

		glUniform1f(x_u_location, SDL_GetTicks() / 10000.f);
		glUniform1f(y_u_location, SDL_GetTicks() / 1000.f);
		glUniform1f(z_u_location, SDL_GetTicks() / 100000.f);

#if CUBE
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
#else
		GLCall(glDrawArrays(GL_TRIANGLES, 0, model.vertecies.back));
#endif
		SDL_GL_SwapWindow(Window);
	}
	return 0;
}