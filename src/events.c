#include "scop.h"

unsigned 	WindowShouldClose(SDL_Event e)
{
	return (e.type == SDL_QUIT
		|| (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE)
		|| (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE));
}

unsigned	scop_error(const char *error)
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

void		GLClearError()
{
	while (glGetError());
}

char		GLCheckError(const char *Function, const char *File, int Line)
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

void			handle_rotations_and_scale(SDL_Event e, t_frame_info *frame, unsigned key_down)
{
	if (e.key.keysym.sym == 'h')
		frame->angles_offset.y = key_down ? -1.f : 0;
	else if (e.key.keysym.sym == 'l')
		frame->angles_offset.y = key_down ? 1.f : 0;
	else if (e.key.keysym.sym == 'k')
		frame->angles_offset.x = key_down ? 1.f : 0;
	else if (e.key.keysym.sym == 'j')
		frame->angles_offset.x = key_down ? -1.f : 0;
	else if (e.key.keysym.sym == '=')
		frame->scale_dir = key_down ? .2f : 0;
	else if (e.key.keysym.sym == '-')
		frame->scale_dir = key_down ? -.2f : 0;
}

void			handle_translation(SDL_Event e, t_frame_info *frame, unsigned key_down)
{
	if (e.key.keysym.sym == SDLK_PAGEUP)
		frame->position_offset.z = key_down ? 1 : 0;
	else if (e.key.keysym.sym == SDLK_PAGEDOWN)
		frame->position_offset.z = key_down ? -1 : 0;
	else if (e.key.keysym.sym == SDLK_UP)
		frame->position_offset.y = key_down ? 1 : 0;
	else if (e.key.keysym.sym == SDLK_DOWN)
		frame->position_offset.y = key_down ? -1 : 0;
	else if (e.key.keysym.sym == SDLK_RIGHT)
		frame->position_offset.x = key_down ? 1 : 0;
	else if (e.key.keysym.sym == SDLK_LEFT)
		frame->position_offset.x = key_down ? -1 : 0;
}



unsigned		pre_draw(t_frame_info *frame)
{
	SDL_Event	e;

	frame->last_time = frame->current_time;
	frame->current_time = SDL_GetTicks();
	frame->delta_time = (frame->current_time - frame->last_time) / 1000.f;
	GLCall(glClearColor(0.0, 0.1, 0.01, 0));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	while (SDL_PollEvent(&e))
	{
		if (WindowShouldClose(e))
			return 0;
		if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
		{
			handle_rotations_and_scale(e, frame, e.type == SDL_KEYDOWN);
			handle_translation(e, frame, e.type == SDL_KEYDOWN);
			if (e.key.keysym.sym == '1')
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else if (e.key.keysym.sym == '2')
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
	return 1;
}

void		draw(t_frame_info *frame, t_model *model)
{
		if (frame->angles_offset.x || frame->angles_offset.y)
		{
			frame->angles += frame->angles_offset * frame->delta_time;
			glUniform2fv(frame->angles_u_location, 1, &frame->angles);
		}
		if (frame->position_offset.x || frame->position_offset.y || frame->position_offset.z)
		{
			frame->position += frame->position_offset * frame->delta_time;
			glUniform3fv(frame->position_u_location, 1, &frame->position);
		}
		if (frame->scale_dir)
		{
			frame->scale += frame->scale_dir * frame->delta_time;
			frame->scale = max(frame->scale, 0.001);
			glUniform1f(frame->scale_u_location, frame->scale);
		}
		//GLCall(glEnable(GL_BLEND));
		//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glDrawArrays(GL_TRIANGLES, 0, model->vertecies.back));
}

int			event_loop(SDL_Window *window, t_model *model)
{
	t_frame_info frame;

	while (pre_draw(&frame))
	{
		SDL_GL_SwapWindow(window);
	}
}