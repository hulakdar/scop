/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m44.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 23:41:11 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/14 00:06:01 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_math.h"
#include <stdint.h>

t_m44		m_identity(void)
{
	t_m44			m;

	m.m[0] = (t_float4) {1, 0, 0, 0};
	m.m[1] = (t_float4) {0, 1, 0, 0};
	m.m[2] = (t_float4) {0, 0, 1, 0};
	m.m[3] = (t_float4) {0, 0, 0, 1};
	return (m);
}

t_m44		m_look_at(t_float4 from, t_float4 to)
{
	const t_float4	forward = normalize(from - to);
	const t_float4	right = cross_product((t_float4){ 0, 1, 0 }, forward);
	const t_float4	up = cross_product(forward, right);
	t_m44			world_to_cam;

	world_to_cam.m[0] = right;
	world_to_cam.m[1] = up;
	world_to_cam.m[2] = forward;
	world_to_cam.m[3] = from;
	return (world_to_cam);
}

t_float4	mult_vec_matrix(t_float4 v, t_m44 m)
{
	t_float4 out;

	out.x = v.x * m.m[0].x + v.y * m.m[1].x + v.z * m.m[2].x + v.w * m.m[3].x;
	out.y = v.x * m.m[0].y + v.y * m.m[1].y + v.z * m.m[2].y + v.w * m.m[3].y;
	out.z = v.x * m.m[0].z + v.y * m.m[1].z + v.z * m.m[2].z + v.w * m.m[3].z;
	out.w = v.x * m.m[0].w + v.y * m.m[1].w + v.z * m.m[2].w + v.w * m.m[3].w;
	return (out);
}

t_m44		mult_matrix(t_m44 lhs, t_m44 rhs)
{
	t_m44			result;
	uint_fast8_t	i;

	i = -1;
	while (++i < 4)
		result.m[i] = mult_vec_matrix(lhs.m[i], rhs);
	return (result);
}

t_m44		m_world(void)
{
	return ((t_m44) {.m = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, -2.5, 1}
	}});
}
