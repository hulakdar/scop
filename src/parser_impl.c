/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_impl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 23:28:29 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/13 23:35:57 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <stdio.h>
#include <math.h>

void	push_vert(t_face face, t_obj *buffers, int i)
{
	t_vertex new_vert;
	t_float4 mask;

	ft_bzero(&new_vert, sizeof(new_vert));
	new_vert.position = *(t_float4 *)ft_vec_get(
		&buffers->positions, face.pos_indx[i]);
	if (face.uvs_indx[i])
		new_vert.uv = *(t_float2 *)ft_vec_get(
			&buffers->uvs, face.uvs_indx[i]);
	if (face.norm_indx[i])
		new_vert.normal = *(t_float4 *)ft_vec_get(
			&buffers->normals, face.norm_indx[i]);
	ft_vec_pushback(&buffers->result->vertecies, &new_vert);
	mask = __builtin_convertvector(
		(new_vert.position < buffers->min_bounds), t_float4);
	buffers->min_bounds =
		new_vert.position * (-mask) + buffers->min_bounds * (1 + mask);
	mask = __builtin_convertvector(
		(new_vert.position > buffers->max_bounds), t_float4);
	buffers->max_bounds =
		new_vert.position * (-mask) + buffers->max_bounds * (1 + mask);
}

void	process_face(t_face face, t_obj *buffers, int count)
{
	push_vert(face, buffers, 0);
	push_vert(face, buffers, 1);
	push_vert(face, buffers, 2);
	buffers->current_object->count += 3;
	fixup_normals(&buffers->result->vertecies, face);
	fixup_uvs(&buffers->result->vertecies, face);
	while (count > 3)
	{
		push_vert(face, buffers, count - 4);
		push_vert(face, buffers, count - 2);
		push_vert(face, buffers, count - 1);
		buffers->current_object->count += 3;
		fixup_normals(&buffers->result->vertecies, face);
		fixup_uvs(&buffers->result->vertecies, face);
		count--;
	}
}

void	parse_single_vert(char *text, t_face *face, int i, int slashes)
{
	char	**tmp;
	int		tmp_size;

	tmp = ft_strsplit(text, '/');
	tmp_size = ft_tabcount(tmp);
	face->pos_indx[i] = ft_atoi(tmp[0]);
	if (slashes == 1 || tmp_size == 3)
		face->uvs_indx[i] = ft_atoi(tmp[1]);
	if (slashes == 2 || tmp_size == 2)
		face->norm_indx[i] = ft_atoi(tmp[tmp_size == 2 ? 1 : 2]);
	ft_tabdel(&tmp);
}

int		parse_face(t_face *face, const char *line)
{
	int		i;
	char	**tab;
	int		count;
	int		slashes;

	tab = ft_strsplit(line, ' ');
	count = ft_tabcount(tab);
	if (count > 16 || count < 3)
		exit(scop_error("Wrong number of verts in face"));
	ft_bzero(face, sizeof(t_face));
	i = -1;
	while (++i < count)
	{
		slashes = ft_chrcnt(tab[i], '/');
		if (slashes)
			parse_single_vert(tab[i], face, i, slashes);
		else
			face->pos_indx[i] = ft_atoi(tab[i]);
	}
	ft_tabdel(&tab);
	return (count);
}

void	parse_faces(const char *line, t_obj *buffers)
{
	t_face		face;
	const int	count = parse_face(&face, line);
	t_float4	half_extent;

	pthread_mutex_lock(&buffers->result->lock);
	process_face(face, buffers, count);
	half_extent = (buffers->max_bounds - buffers->min_bounds) / 2;
	buffers->result->offset_scale = buffers->min_bounds + half_extent;
	half_extent *= half_extent;
	half_extent.w = 1 / sqrtf(half_extent.x + half_extent.y + half_extent.z);
	buffers->result->offset_scale.w = half_extent.w;
	buffers->result->is_dirty = 1;
	pthread_mutex_unlock(&buffers->result->lock);
}
