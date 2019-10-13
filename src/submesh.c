/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   submesh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 23:21:14 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/13 23:24:06 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj.h"

void	create_new_submesh(t_obj *buffers)
{
	t_submesh submesh;

	ft_bzero(&submesh, sizeof(t_submesh));
	submesh.start = buffers->result->vertecies.back;
	buffers->current_object =
		(t_submesh *)ft_vec_pushback(&buffers->result->submeshes, &submesh);
}

void	fixup_uvs(t_vector *vertecies, t_face face)
{
	t_float4	normal;
	t_vertex	*triangle;
	t_float2	uvs[3];
	int			i;

	if (face.uvs_indx[0] || face.uvs_indx[1] || face.uvs_indx[2])
		return ;
	triangle = (t_vertex *)ft_vec_get(vertecies, vertecies->back - 3);
	i = 0;
	while (i < 3)
	{
		uvs[0] = triangle[i].position.yz;
		uvs[1] = triangle[i].position.xz;
		uvs[2] = triangle[i].position.xy;
		normal = triangle[i].normal * triangle[i].normal;
		triangle[i].uv =
			uvs[0] * normal.x +
			uvs[1] * normal.y +
			uvs[2] * normal.z;
		i++;
	}
}

void	fixup_normals(t_vector *vertecies, t_face face)
{
	t_vertex	*triangle;
	t_float4	positions[3];
	t_float4	normal;

	if (face.norm_indx[0] || face.norm_indx[1] || face.norm_indx[2])
		return ;
	triangle = (t_vertex *)ft_vec_get(vertecies, vertecies->back - 3);
	positions[0] = triangle[0].position;
	positions[1] = triangle[1].position;
	positions[2] = triangle[2].position;
	normal = calculate_normal(positions[0], positions[1], positions[2]);
	triangle[0].normal = normal;
	triangle[1].normal = normal;
	triangle[2].normal = normal;
}
