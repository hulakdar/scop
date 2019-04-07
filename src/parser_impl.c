#include "obj.h"
#include "scop.h"
#include <stdio.h>

void parse_vec3(const char *line, t_vector *buffer)
{
	t_float4 result;

	result = (t_float4) (0.f);
	while (*line == ' ')
		line++;
	result.x = ft_atof(line);
	if ((line = ft_strchr(line, ' ')))
	{
		result.y = ft_atof(line + 1);
		if ((line = ft_strchr(line + 1, ' ')))
			result.z = ft_atof(line + 1);
	}

	ft_vec_pushback(buffer, &result);
}

void parse_vec2(const char *line, t_vector *buffer)
{
	t_float2 result;

	result = (t_float2) (0.f);
	while (*line == ' ')
		line++;
	result.x = ft_atof(line + 1);
	if ((line = ft_strchr(line + 1, ' ')))
		result.y = ft_atof(line + 1);
	else
		__debugbreak();
	ft_vec_pushback(buffer, &result);
}

static void process_face(t_face face, t_obj *buffers, int i)
{
	t_vertex new_vert = { (0), (0),  (0) };
	new_vert.position = *(t_float4 *)ft_vec_get(&buffers->positions, face.pos_indx[i]);
	//if (face.has_uv)
	new_vert.uv = *(t_float2 *)ft_vec_get(&buffers->uvs, face.uvs_indx[i]);
	//else
		; // panic
	//if (face.has_norm)
		new_vert.normal = *(t_float4 *)ft_vec_get(&buffers->normals, face.norm_indx[i]);
	//else
	; // calculate the fucking normal. don't be a pussy
	ft_vec_pushback(&buffers->result->vertecies, &new_vert);
	buffers->current_object->count++;
}

int parse_face(t_face *face, const char *line)
{
	int			i;
	char		**tab = ft_strsplit(line, ' ');
	const int	count = ft_tabcount(tab);

	i = -1;
	ft_bzero(face, sizeof(t_face));
	while (++i < count)
	{
		char **tmp = ft_strsplit(tab[i], '/');
		const int tmp_size = ft_tabcount(tmp);
		for (int j = 0; j < tmp_size; ++j)
			if (j == 0)
				face->pos_indx[i] = ft_atoi(tmp[j]) - 1;
			else if (j == 1)
				face->uvs_indx[i] = ft_atoi(tmp[j]) - 1;
			else if (j == 2)
				face->norm_indx[i] = ft_atoi(tmp[j]) - 1;
			else
				exit(scop_error("Strange number of idx in a vert. Something is wrong. \n"));
	}
	ft_tabdel(&tab);
	return count;
}

void create_new_submesh(t_obj * buffers)
{
	t_submesh submesh;

	ft_bzero(&submesh, sizeof(t_submesh));
	submesh.start = buffers->result->vertecies.back;
	buffers->current_object = (t_submesh *)ft_vec_pushback(&buffers->result->submeshes, &submesh);
}

void parse_faces(const char *line, t_obj *buffers)
{
	int			i;
	t_face		face;
	const int	count = parse_face(&face, line);

	if (!buffers->current_object)
		create_new_submesh(buffers);
	if (count > 4 || count < 3)
		exit(scop_error("Strange number of verts in a face. Something is wrong. \n"));
	i = -1;
	pthread_mutex_lock(&buffers->result->lock);
	while (++i < 3)
		process_face(face, buffers, i);
	i = -1;
	if (count == 4)
		while (++i < 4)
			process_face(face, buffers, i == 1 ? ++i : i);
	buffers->result->is_dirty = 1;
	pthread_mutex_unlock(&buffers->result->lock);
}
