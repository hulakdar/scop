/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 22:34:18 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/14 00:05:53 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_MATH_H
# define GL_MATH_H

# define _USE_MATH_DEFINES
# include <math.h>

typedef float	t_float16 __attribute__((ext_vector_type(16)));
typedef float	t_float8 __attribute__((ext_vector_type(8)));
typedef float	t_float4 __attribute__((ext_vector_type(4)));
typedef float	t_float2 __attribute__((ext_vector_type(2)));
typedef int		t_int4 __attribute__((ext_vector_type(4)));

typedef struct	s_vertex
{
	t_float4	position;
	t_float4	normal;
	t_float2	uv;
}				t_vertex;

typedef struct	s_m44
{
	t_float4	m[4];
}				t_m44;

t_float2		frustum(float angle_of_view, float image_aspect_ratio, float n);
t_m44			perspective(t_float2 tr, float n, float f);
t_m44			orthographic(t_float2 tr, float n, float f);
t_float4		mult_vec_matrix(t_float4 in, t_m44 m);
t_m44			mult_matrix(t_m44 lhs, t_m44 rhs);
t_float4		calculate_normal(t_float4 p1, t_float4 p2, t_float4 p3);
t_float4		cross_product(t_float4 lhs, t_float4 rhs);
t_float4		normalize(t_float4 v);
t_m44			m_identity();
t_m44			m_look_at(t_float4 from, t_float4 to);
t_m44			m_model(t_float2 angles, t_float4 position, float scale);
t_m44			m_world(void);

#endif
