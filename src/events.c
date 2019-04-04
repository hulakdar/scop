#include "scop.h"

char WindowShouldClose(const SDL_Event* e)
{
	return (e->type == SDL_QUIT
		|| (e->type == SDL_WINDOWEVENT && e->window.event == SDL_WINDOWEVENT_CLOSE)
		|| (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE));
}

char scop_error(const char *error)
{
	ft_putstr_fd(error, 2);
#if _MSC_VER
	if (IsDebuggerPresent())
		__debugbreak();
#else
	asm("int $3");
#endif 
	return -1;
}

void GLClearError()
{
	while (glGetError());
}

char GLCheckError(const char *Function, const char *File, int Line)
{
	(void)Function;
	(void)File;
	(void)Line;
	GLenum Error;
	while ((Error = glGetError()))
	{
#if _WIN32 || _WIN64
		__debugbreak();
#else
		continue;
#endif
	}
	return 1;
}

int event_loop(SDL_Window *window, t_model model)
{
	Uint64	last_time = 0;
	Uint64	current_time = 0;
	float	delta_time = 0;

	int		angles_u_location = glGetUniformLocation(model.shader_program, "u_angles");
	int		position_u_location = glGetUniformLocation(model.shader_program, "u_position");
	int		scale_u_location = glGetUniformLocation(model.shader_program, "u_scale");
	float	scale = 0.01;
	float	scale_dir = 0;
	t_float2	angles = (0);
	t_float2	angles_offset = angles;
	t_float4	position = (0);
	t_float4	position_offset = (0);

	SDL_Event	e;
	while (1)
	{
		last_time = current_time;
		current_time = SDL_GetTicks();
		delta_time = (current_time - last_time) / 1000.f;
		GLCall(glClearColor(0.0, 0.1, 0.01, 0));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		while (SDL_PollEvent(&e))
		{
			if (WindowShouldClose(&e))
				return 0;
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == 'h')
					angles_offset.y = -1.f;
				else if (e.key.keysym.sym == 'l')
					angles_offset.y = 1.f;
				else if (e.key.keysym.sym == 'k')
					angles_offset.x = 1.f;
				else if (e.key.keysym.sym == 'j')
					angles_offset.x = -1.f;
				else if (e.key.keysym.sym == '=')
					scale_dir = 0.2;
				else if (e.key.keysym.sym == '-')
					scale_dir = -0.2;
				else if (e.key.keysym.sym == SDLK_PAGEUP)
					position_offset.z = 1;
				else if (e.key.keysym.sym == SDLK_PAGEDOWN)
					position_offset.z = -1;
				else if (e.key.keysym.sym == SDLK_UP)
					position_offset.y = 1;
				else if (e.key.keysym.sym == SDLK_DOWN)
					position_offset.y = -1;
				else if (e.key.keysym.sym == SDLK_RIGHT)
					position_offset.x = 1;
				else if (e.key.keysym.sym == SDLK_LEFT)
					position_offset.x = -1;
				else if (e.key.keysym.sym == '1')
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				else if (e.key.keysym.sym == '2')
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else if (e.type == SDL_KEYUP)
			{
				if (e.key.keysym.sym == 'h')
					angles_offset.y = 0;
				else if (e.key.keysym.sym == 'l')
					angles_offset.y = 0;
				else if (e.key.keysym.sym == 'k')
					angles_offset.x = 0;
				else if (e.key.keysym.sym == 'j')
					angles_offset.x = 0;
				else if (e.key.keysym.sym == '=')
					scale_dir = 0;
				else if (e.key.keysym.sym == '-')
					scale_dir = 0;
				else if (e.key.keysym.sym == SDLK_PAGEUP)
					position_offset.z = 0;
				else if (e.key.keysym.sym == SDLK_PAGEDOWN)
					position_offset.z = 0;
				else if (e.key.keysym.sym == SDLK_UP)
					position_offset.y = 0;
				else if (e.key.keysym.sym == SDLK_DOWN)
					position_offset.y = 0;
				else if (e.key.keysym.sym == SDLK_RIGHT)
					position_offset.x = 0;
				else if (e.key.keysym.sym == SDLK_LEFT)
					position_offset.x = 0;
			}
		}
		if (angles_offset.x || angles_offset.y)
		{
			angles += angles_offset * delta_time;
			glUniform2fv(angles_u_location, 1, &angles);
		}
		if (position_offset.x || position_offset.y || position_offset.z)
		{
			position += position_offset * delta_time;
			glUniform3fv(position_u_location, 1, &position);
		}
		if (scale_dir)
		{
			scale += scale_dir * delta_time;
			scale = max(scale, 0.001);
			glUniform1f(scale_u_location, scale);
		}
		//GLCall(glEnable(GL_BLEND));
		//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glDrawArrays(GL_TRIANGLES, 0, model.vertecies.back));
		SDL_GL_SwapWindow(window);
	}
}