#include "obj.h"
#include "scop.h"

void parse_vec3(const char *line, t_vector *buffer)
{
	t_vec3 result;

	result = (t_vec3) { 0, 0, 0 };
	while (*line == ' ')
		line++;
	result.x = ft_atof(line);
	if ((line = ft_strchr(line, ' ')))
	{
		result.y = ft_atof(line);
		if ((line = ft_strchr(line, ' ')))
			result.z = ft_atof(line);
	}
	ft_vec_pushback(buffer, &result);
}

void parse_vec2(const char *line, t_vector *buffer)
{
	t_vec2 result;

	result = (t_vec2) { 0, 0 };
	while (*line == ' ')
		line++;
	result.x = ft_atof(line);
	if ((line = ft_strchr(line, ' ')))
		result.y = ft_atof(line);
	ft_vec_pushback(buffer, &result);
}

void parse_faces(const char *line, t_obj *buffers, t_model *model)
{
	const char	**tab = ft_strsplit(line, ' ');
	const int	count = ft_tabcount(tab);
	int			i;
	t_face		face = { 0 };
	const char	*seeker;

	if (count > 4 || count < 3)
		exit(scop_error("Strange number of verts in a face. Something is wrong. \n"));
	i = -1;
	while (++i < count)
	{
		char **tmp = ft_strsplit(tab[i], '/');
		const int tmp_size = ft_tabcount(tmp);
		for (int j = 0; j < tmp_size; ++j)
			if (j == 0)
				face.pos_indx[i] = ft_atoi(tmp[j]);
			else if (j == 1)
				face.uvs_indx[i] = ft_atoi(tmp[j]);
			else if (j == 2)
				face.norm_indx[i] = ft_atoi(tmp[j]);
			else
				exit(scop_error("Strange number of idx in a vert. Something is wrong. \n"));
		seeker = tab[i];
	}
	i = -1;
	while (++i < 3)
	{
		t_vertex new_vert = { 0 };
		new_vert.position = *(t_vec3 *)ft_vec_get(&buffers->positions, face.pos_indx[i]);
#if WITH_SHIT
		if (face.has_uv)
			new_vert.uv = *(t_vec2 *)ft_vec_get(&buffers->uvs, face.uvs_indx[i]);
		else
			; // panic
		if (face.has_norm)
			new_vert.normale = *(t_vec3 *)ft_vec_get(&buffers->normals, face.norm_indx[i]);
		else
			; // calculate the fucking normal. don't be a pussy
#endif
		ft_vec_pushback(&model->vertecies, &new_vert);
	}
	if (count == 4)
	{
		i = 0;
		while (++i < count)
		{
			t_vertex new_vert = { 0 };
			new_vert.position = *(t_vec3 *)ft_vec_get(&buffers->positions, face.pos_indx[i]);
#if WITH_SHIT
			if (face.has_uv)
				new_vert.uv = *(t_vec2 *)ft_vec_get(&buffers->uvs, face.uvs_indx[i]);
			else
				; // panic
			if (face.has_norm)
				new_vert.normale = *(t_vec3 *)ft_vec_get(&buffers->normals, face.norm_indx[i]);
			else
				; // calculate the fucking normal. don't be a pussy
#endif
			ft_vec_pushback(&model->vertecies, &new_vert);
		}
	}
}
	

void parse_mtl(const char *line, t_vector *materials)
{
	printf("Found material. not implemented yet: %s\n", line);
}
