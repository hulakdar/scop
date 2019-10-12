
#include "obj.h"

void create_new_submesh(t_obj * buffers)
{
	t_submesh submesh;

	ft_bzero(&submesh, sizeof(t_submesh));
	submesh.start = buffers->result->vertecies.back;
	buffers->current_object =
		(t_submesh *)ft_vec_pushback(&buffers->result->submeshes, &submesh);
}

__attribute__((noinline))
void fixup_uvs(t_vector *vertecies, t_face face)
{
	t_vertex *triangle;
	t_float2	uvs[3];

	if (face.uvs_indx[0] || face.uvs_indx[1] || face.uvs_indx[2])
		return;
	triangle = (t_vertex *)ft_vec_get(vertecies, vertecies->back - 3);
	for (int i = 0; i < 3; ++i)
	{
		uvs[0] = triangle[i].position.yz;
		uvs[1] = triangle[i].position.xz;
		uvs[2] = triangle[i].position.xy;
		t_float4 normal = SQUARE(triangle[i].normal);
		triangle[i].uv = uvs[0] * normal.x + uvs[1] * normal.y + uvs[2] * normal.z;
	}
}

__attribute__((noinline))
void fixup_normals(t_vector *vertecies, t_face face)
{
	t_vertex *triangle;
	t_float4 positions[3];
	t_float4 normal;

	if (face.norm_indx[0] || face.norm_indx[1] || face.norm_indx[2])
		return;
	triangle = (t_vertex *)ft_vec_get(vertecies, vertecies->back - 3);
	positions[0] = triangle[0].position;
	positions[1] = triangle[1].position;
	positions[2] = triangle[2].position;
	normal = calculate_normal(positions[0], positions[1], positions[2]);
	triangle[0].normal = normal;
	triangle[1].normal = normal;
	triangle[2].normal = normal;
}

