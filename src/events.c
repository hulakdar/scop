/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 23:45:16 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/13 23:47:19 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "shaders.h"

static unsigned	should_exit(SDL_Event e)
{
	return (e.type == SDL_QUIT
		|| (e.type == SDL_WINDOWEVENT
		&& e.window.event == SDL_WINDOWEVENT_CLOSE)
		|| (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE));
}

static void		handle_keyboard(SDL_Keycode sym,
								t_frame_info *frame, unsigned key_down)
{
	if (sym == '1' && key_down)
		frame->polygon_mode = GL_FILL;
	else if (sym == '2' && key_down)
		frame->polygon_mode = GL_LINE;
	else if (sym == '3' && key_down)
		frame->polygon_mode = GL_POINT;
}

static void		handle_mouse(SDL_MouseMotionEvent e, t_frame_info *frame)
{
	if (e.state & SDL_BUTTON_LMASK)
	{
		frame->angles.y += e.xrel / 180.f;
		frame->angles.x += e.yrel / 180.f;
	}
}

t_bool			update(t_frame_info *frame)
{
	SDL_Event	e;

	frame->last_time = frame->current_time;
	frame->current_time = SDL_GetTicks();
	frame->delta_time = (frame->current_time - frame->last_time) / 1000.f;
	while (SDL_PollEvent(&e))
	{
		if (should_exit(e))
			return (0);
		if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
			handle_keyboard(e.key.keysym.sym, frame, e.type == SDL_KEYDOWN);
		else if (e.type == SDL_MOUSEMOTION)
			handle_mouse(e.motion, frame);
	}
	return (1);
}
