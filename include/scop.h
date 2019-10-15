/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 22:41:40 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/13 23:25:53 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include "common.h"
# include "obj.h"
# include "events.h"

# define SCREEN_W 1024
# define SCREEN_H 1024

typedef	struct	s_global_uniforms
{
	t_m44		mvp;
	t_m44		light_view;
	float		scale;
}				t_global_uniforms;

typedef struct	s_frame_info
{
	t_global_uniforms	g_uniforms;
	t_float4			position;
	t_float2			angles;
	t_float2			light_angles;
	uint64_t			last_time;
	uint64_t			current_time;
	GLuint				uniform_buffer;
	GLuint				default_texture;
	GLenum				polygon_mode;
	float				delta_time;
	float				scale;
	uint_fast8_t		is_dirty;
}				t_frame_info;

typedef	uint_fast8_t	t_bool;

enum					e_bool_values
{
	false = 0,
	true = 1
};

unsigned		scop_error(const char *error);
GLuint			create_texture_cube(const char *folder);
GLuint			create_texture_2d(const char *filename);
void			draw(t_frame_info *frame, t_model *model);
void			draw_quad(t_quad_data quad_data);
t_bool			update(t_frame_info *frame);

#endif
