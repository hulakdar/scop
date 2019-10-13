/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 23:40:17 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/13 23:40:58 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		prepare_frame_info(t_frame_info *frame)
{
	ft_bzero(frame, sizeof(t_frame_info));
	frame->polygon_mode = GL_FILL;
	frame->scale = 1;
	GLCALL(glGenBuffers(1, &frame->uniform_buffer));
	GLCALL(glBindBuffer(GL_UNIFORM_BUFFER, frame->uniform_buffer));
	GLCALL(glBufferData(GL_UNIFORM_BUFFER, sizeof(t_global_uniforms),
		&frame->g_uniforms, GL_DYNAMIC_DRAW));
	GLCALL(glBindBufferBase(GL_UNIFORM_BUFFER, 0, frame->uniform_buffer));
	frame->default_texture = create_texture_2d("res/default.png");
}

void		calculate_shader_uniforms(t_frame_info *frame, t_model *model)
{
	t_float4	position;
	float		scale;

	position = -model->offset_scale;
	scale = -position.w;
	position.w = 1;
	frame->g_uniforms.mvp = mult_matrix(mult_matrix(
		m_model(frame->angles, position, scale * 1.4), m_world()),
		perspective(frustum(70, 1, .5f), .5f, 8));
	frame->g_uniforms.scale = scale;
	GLCALL(glBufferSubData(GL_UNIFORM_BUFFER, 0,
		sizeof(t_global_uniforms), &frame->g_uniforms));
}

void		event_loop(SDL_Window *window, t_model *model)
{
	t_frame_info	frame;

	prepare_frame_info(&frame);
	while (update(&frame))
	{
		calculate_shader_uniforms(&frame, model);
		pthread_mutex_lock(&model->lock);
		if (model->is_dirty)
		{
			bind_buffers(model->buffers);
			GLCALL(glBufferData(GL_ARRAY_BUFFER,
				model->vertecies.back * model->vertecies.size_of_type,
				model->vertecies.data, GL_STATIC_DRAW));
			model->is_dirty = 0;
		}
		SDL_GL_MakeCurrent(model->window, model->context);
		draw(&frame, model);
		pthread_mutex_unlock(&model->lock);
		SDL_GL_SwapWindow(window);
	}
}
