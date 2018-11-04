#include "scop.h"

char WindowShouldClose(const SDL_Event* e)
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
	int x_u_location = glGetUniformLocation(model.shader_program, "x");
	int y_u_location = glGetUniformLocation(model.shader_program, "y");
	float x_angle = 0;
	float y_angle = 0;
	float x_dir = 0;
	float y_dir = 0;

	SDL_Event	e;
	while (1)
	{
		glClearColor(0.8, 0.5, 0.7, 0);
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		while (SDL_PollEvent(&e))
		{
			if (WindowShouldClose(&e))
				return 0;
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == 'h')
					y_dir = -1.f;
				else if (e.key.keysym.sym == 'l')
					y_dir = 1.f;
				else if (e.key.keysym.sym == 'k')
					x_dir = 1.f;
				else if (e.key.keysym.sym == 'j')
					x_dir = -1.f;
				else if (e.key.keysym.sym == '1')
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				else if (e.key.keysym.sym == '2')
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else if (e.type == SDL_KEYUP)
			{
				if (e.key.keysym.sym == 'h')
					y_dir = 0;
				else if (e.key.keysym.sym == 'l')
					y_dir = 0;
				else if (e.key.keysym.sym == 'k')
					x_dir = 0;
				else if (e.key.keysym.sym == 'j')
					x_dir = 0;
			}
		}
		if (x_dir)
		{
			x_angle += x_dir * SDL_GetTicks() / 900000.f;
			glUniform1f(x_u_location, x_angle);
		}
		if (y_dir)
		{
			y_angle += y_dir * SDL_GetTicks() / 900000.f;
			glUniform1f(y_u_location, y_angle);
		}
		GLCall(glDrawArrays(GL_TRIANGLES, 0, model.vertecies.back));
		SDL_GL_SwapWindow(window);
	}
}