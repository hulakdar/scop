/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 23:24:45 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/14 00:31:45 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

t_float4	calculate_normal(t_float4 p1, t_float4 p2, t_float4 p3)
{
	t_float4 normal;
	t_float4 u;
	t_float4 v;

	u = p2 - p1;
	v = p3 - p1;
	normal = cross_product(u, v);
	return (normalize(normal));
}

t_float4	parse_vec3(const char *line)
{
	t_float4 result;

	while (*line == ' ')
		line++;
	result = (t_float4)(0.f);
	result.x = ft_atof(line);
	if ((line = ft_strchr(line, ' ')))
	{
		result.y = ft_atof(line + 1);
		if ((line = ft_strchr(line + 1, ' ')))
			result.z = ft_atof(line + 1);
	}
	return (result);
}

t_float2	parse_vec2(const char *line)
{
	t_float2 result;

	while (*line == ' ')
		line++;
	result = (t_float2)(0.f);
	while (*line == ' ')
		line++;
	result.x = ft_atof(line + 1);
	if ((line = ft_strchr(line + 1, ' ')))
		result.y = ft_atof(line + 1);
	return (result);
}
