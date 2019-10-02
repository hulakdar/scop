#include "obj.h"

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

t_float4 parse_vec3(const char *line)
{
	t_float4 result;

	while (*line == ' ')
		line++;
	result = (t_float4) (0.f);
	result.x = ft_atof(line);
	if ((line = ft_strchr(line, ' ')))
	{
		result.y = ft_atof(line + 1);
		if ((line = ft_strchr(line + 1, ' ')))
			result.z = ft_atof(line + 1);
	}
	return result;
}

t_float2 parse_vec2(const char *line)
{
	t_float2 result;

	while (*line == ' ')
		line++;
	result = (t_float2) (0.f);
	while (*line == ' ')
		line++;
	result.x = ft_atof(line + 1);
	if ((line = ft_strchr(line + 1, ' ')))
		result.y = ft_atof(line + 1);
	return result;
}
