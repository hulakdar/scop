/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 23:06:23 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/14 00:34:51 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"
#include "scop.h"
#include "shaders.h"
#include <stdio.h>

static void	prepare_obj(t_obj *obj)
{
	const t_float4	tmp = {0, 0, 0, 0};

	ft_bzero(obj, sizeof(t_obj));
	ft_vec_init(&obj->positions, sizeof(t_float4), 256);
	ft_vec_init(&obj->normals, sizeof(t_float4), 256);
	ft_vec_init(&obj->uvs, sizeof(t_float2), 256);
	ft_vec_pushback(&obj->positions, &tmp);
	ft_vec_pushback(&obj->normals, &tmp);
	ft_vec_pushback(&obj->uvs, &tmp);
}

static void	handle_vec(const char *line, t_vector *buffer, t_bool is_vec3)
{
	void		*result;
	t_float4	vec4;
	t_float2	vec2;

	while (*line == ' ')
		line++;
	if (is_vec3)
	{
		vec4 = parse_vec3(line);
		result = &vec4;
	}
	else
	{
		vec2 = parse_vec2(line);
		result = &vec2;
	}
	ft_vec_pushback(buffer, result);
}

static void	set_mtl(const char *line, t_obj *obj)
{
	t_material	*candidate;
	size_t		i;

	i = 0;
	while (i < obj->result->materials.back)
	{
		candidate = (t_material*)
			ft_vec_get(&obj->result->materials, i);
		if (ft_strcmp(line, candidate->name) == 0)
		{
			obj->current_object->material = candidate;
		}
		i++;
	}
}

static void	parse_single_line(const char *line, t_obj *obj)
{
	while (!ft_isprint(*line))
		line++;
	if (!ft_memcmp(line, "v ", 2))
		handle_vec(line + 2, &obj->positions, true);
	else if (!ft_memcmp(line, "vn ", 3))
		handle_vec(line + 3, &obj->normals, true);
	else if (!ft_memcmp(line, "vt ", 3))
		handle_vec(line + 3, &obj->uvs, false);
	else if (!ft_memcmp(line, "f ", 2))
		parse_faces(line + 2, obj);
	else if (!ft_memcmp(line, "mtllib ", 7))
		parse_mtl(line + 7, obj);
	else if (!ft_memcmp(line, "usemtl ", 7))
		set_mtl(line + 7, obj);
	else if (!ft_memcmp(line, "o ", 2))
		create_new_submesh(obj);
	else
	{
		ft_putendl("Unknown in .obj: ");
		ft_putendl(line);
	}
}

void		*parse_obj(t_model *model)
{
	const int	fd = open(model->filepath, O_RDONLY);
	t_obj		obj;
	char		*line;

	prepare_obj(&obj);
	obj.result = model;
	create_new_submesh(&obj);
	if (fd > 2)
	{
		while (get_next_line(fd, &line) > 0 && !model->request_exit)
		{
			if (*line != '#' && *line != '\n' && *line)
				parse_single_line(line, &obj);
			free(line);
		}
		close(fd);
	}
	if ((model->request_exit = model->vertecies.back < 1))
		scop_error("No vertecies in this file");
	ft_vec_del(&obj.positions);
	ft_vec_del(&obj.normals);
	ft_vec_del(&obj.uvs);
	return (NULL);
}
