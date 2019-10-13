/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 23:50:53 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/14 00:08:56 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_math.h"

t_m44		m_rotate(t_float2 angles)
{
	t_m44 y_axis;
	t_m44 x_axis;

	y_axis = (t_m44){.m = {
		{cosf(angles.y), 0, -sinf(angles.y), 0},
		{0, 1, 0, 0},
		{sinf(angles.y), 0, cosf(angles.y), 0},
		{0, 0, 0, 1}}};
	x_axis = (t_m44){.m = {
		{1, 0, 0, 0},
		{0, cosf(angles.x), sinf(angles.x), 0},
		{0, -sinf(angles.x), cosf(angles.x), 0},
		{0, 0, 0, 1}}};
	return (mult_matrix(y_axis, x_axis));
}

t_m44		m_model(t_float2 angles, t_float4 position, float scale)
{
	t_m44 offset;
	t_m44 scaling;

	offset = (t_m44){ .m = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		position
	}};
	scaling = (t_m44){ .m = {
		{scale, 0, 0, 0},
		{0, scale, 0, 0},
		{0, 0, scale, 0},
		{0, 0, 0, 1}
	}};
	return (mult_matrix(mult_matrix(offset, scaling), m_rotate(angles)));
}

t_float4	cross_product(t_float4 lhs, t_float4 rhs)
{
	return (t_float4) {
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x,
		0
	};
}

t_float4	normalize(t_float4 v)
{
	float		length_squared;
	t_float4	squared;

	squared = v * v;
	length_squared = squared.x + squared.y + squared.z;
	return (v / sqrtf(length_squared));
}
