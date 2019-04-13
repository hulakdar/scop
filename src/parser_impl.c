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

void push_vert(t_face face, t_obj *buffers, int i)
{
	t_vertex new_vert = { (0), (0),  (0) };

	new_vert.position = *(t_float4 *)ft_vec_get(&buffers->positions, face.pos_indx[i]);
	if (!(new_vert.position.x || new_vert.position.y || new_vert.position.z || new_vert.position.w))
		__debugbreak();
	if (face.uvs_indx[i])
		new_vert.uv = *(t_float2 *)ft_vec_get(&buffers->uvs, face.uvs_indx[i]);
	if (face.norm_indx[i])
		new_vert.normal = *(t_float4 *)ft_vec_get(&buffers->normals, face.norm_indx[i]);
	ft_vec_pushback(&buffers->result->vertecies, &new_vert);
	buffers->current_object->count++;
	if (new_vert.position.x < buffers->min_bounds.x)
		buffers->min_bounds.x = new_vert.position.x;
	if (new_vert.position.y < buffers->min_bounds.y)
		buffers->min_bounds.y = new_vert.position.y;
	if (new_vert.position.z < buffers->min_bounds.z)
		buffers->min_bounds.z = new_vert.position.z;
	if (new_vert.position.x > buffers->max_bounds.x)
		buffers->max_bounds.x = new_vert.position.x;
	if (new_vert.position.y > buffers->max_bounds.y)
		buffers->max_bounds.y = new_vert.position.y;
	if (new_vert.position.z > buffers->max_bounds.z)
		buffers->max_bounds.z = new_vert.position.z;
}

t_float4 calculate_normal(t_float4 *positions)
{
	t_float4 normal;
	t_float4 u;
	t_float4 v;

	u = positions[1] - positions[0];
	v = positions[2] - positions[0];
	normal.x = u.y * v.z - u.z * v.y;
	normal.y = u.z * v.x - u.x * v.z;
	normal.z = u.x * v.y - u.y * v.x;
	return normalize(normal);
}

void fixup_normals(t_vector *vertecies)
{
	const t_float4 zero = { 0,0,0,0 };
	t_vertex *triangle;
	t_float4 positions[3];
	t_float4 normal;

	triangle = NULL;
	triangle = (t_vertex *)ft_vec_get(vertecies, vertecies->back - 3);
	positions[0] = triangle[0].position;
	positions[1] = triangle[1].position;
	positions[2] = triangle[2].position;
	normal = calculate_normal(positions);
	if (!ft_memcmp(&triangle[0].normal, &zero, sizeof(t_float4)))
		triangle[0].normal = normal;
	if (!ft_memcmp(&triangle[1].normal, &zero, sizeof(t_float4)))
		triangle[1].normal = normal;
	if (!ft_memcmp(&triangle[2].normal, &zero, sizeof(t_float4)))
		triangle[2].normal = normal;
		
}

static void process_face(t_face face, t_obj *buffers, int count)
{
	int			i;

	i = -1;
	while (++i < 3)
		push_vert(face, buffers, i);
	fixup_normals(&buffers->result->vertecies);
	if (count == 4)
	{
		i = -1;
		while (++i < 4)
			push_vert(face, buffers, i == 1 ? ++i : i);
		fixup_normals(&buffers->result->vertecies);
	}
}

int parse_face(t_face *face, const char *line)
{
	int			i;
	char		**tab = ft_strsplit(line, ' ');
	const int	count = ft_tabcount(tab);

	if (count > 4 || count < 3)
		exit(scop_error("Wrong number of verts in face"));
	ft_bzero(face, sizeof(t_face));
	i = -1;
	while (++i < count)
	{
		const int	slashes = ft_chrcnt(tab[i], '/');
		if (slashes)
		{
			char **tmp = ft_strsplit(tab[i], '/');
			const int tmp_size = ft_tabcount(tmp);
			face->pos_indx[i] = ft_atoi(tmp[0]);
			if (slashes == 1 || tmp_size == 3)
				face->uvs_indx[i] = ft_atoi(tmp[1]);
			if (slashes == 2 || tmp_size == 2)
				face->norm_indx[i] = ft_atoi(tmp[tmp_size == 2 ? 1 : 2]);
			ft_tabdel(&tmp);
		}
		else
			face->pos_indx[i] = ft_atoi(tab[i]);
	}
	ft_tabdel(&tab);
	return count;
}

void create_new_submesh(t_obj * buffers)
{
	t_submesh submesh;

	ft_bzero(&submesh, sizeof(t_submesh));
	submesh.start = buffers->result->vertecies.back;
	buffers->current_object =
		(t_submesh *)ft_vec_pushback(&buffers->result->submeshes, &submesh);
}

void parse_faces(const char *line, t_obj *buffers)
{
	t_face		face;
	const int	count = parse_face(&face, line);

	if (!buffers->current_object)
		create_new_submesh(buffers);
	pthread_mutex_lock(&buffers->result->lock);
	process_face(face, buffers, count);
	t_float4 half_extent = (buffers->max_bounds - buffers->min_bounds) / 2;
	buffers->result->offset_scale = buffers->min_bounds + half_extent;
	half_extent *= half_extent;
	half_extent.w = 1 / sqrtf(half_extent.x + half_extent.y + half_extent.z);
	buffers->result->offset_scale.w = half_extent.w;
	buffers->result->is_dirty = 1;
	pthread_mutex_unlock(&buffers->result->lock);
}
