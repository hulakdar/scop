/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m44_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 00:06:21 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/25 15:10:57 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_math.h"
#include "libft.h"

t_float2	frustum(float angle_of_view, float image_aspect_ratio, float near)
{
	float		right;
	t_float2	tr;
	const float top = tanf(angle_of_view * 0.5 * M_PI / 180) * near;

	right = image_aspect_ratio * top;
	tr[0] = top;
	tr[1] = right;
	return (tr);
}

t_m44		perspective(t_float2 tr, float n, float f)
{
	const float t = tr[0];
	const float r = tr[1];
	const float	b = -r;
	const float	l = -t;
	t_m44		m;

	ft_bzero(&m, sizeof(t_m44));
	m.m[0][0] = 2 * n / (r - l);
	m.m[1][1] = 2 * n / (t - b);
	m.m[0][2] = (r + l) / (r - l);
	m.m[1][2] = (t + b) / (t - b);
	m.m[2][2] = -(f + n) / (f - n);
	m.m[3][2] = -1;
	m.m[2][3] = -2 * f * n / (f - n);
	return (m);
}

t_m44		orthographic(t_float2 tr, float n, float f)
{
	const float t = tr[0];
	const float r = tr[1];
	const float	b = -r;
	const float	l = -t;
	t_m44		m;

	ft_bzero(&m, sizeof(t_m44));
	m.m[0][0] = 2 / (r - l);
	m.m[1][1] = 2 / (t - b);
	m.m[2][2] = -2 / (f - n);
	m.m[3][0] = -(r + l) / (r - l);
	m.m[3][1] = -(t + b) / (t - b);
	m.m[3][2] = -(f + n) / (f - n);
	m.m[3][3] = 1;
	return (m);
}
