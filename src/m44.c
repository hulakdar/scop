#include "gl_math.h"
#include <stdint.h>

t_m44	m_identity()
{
	t_m44			m;

	m.m[0] = (t_float4) {1, 0, 0, 0};
	m.m[1] = (t_float4) {0, 1, 0, 0};
	m.m[2] = (t_float4) {0, 0, 1, 0};
	m.m[3] = (t_float4) {0, 0, 0, 1};
	return m;
}

t_m44 m_look_at(t_float4 from, t_float4 to)
{
	const t_float4	forward = normalize(from - to);
	const t_float4	right = cross_product((t_float4){ 0, 1, 0 }, forward);
	const t_float4	up = cross_product(forward, right);
	t_m44			camToWorld;

	camToWorld.m[0] = right;
	camToWorld.m[1] = up;
	camToWorld.m[2] = forward;
	camToWorld.m[3] = from;
	return camToWorld;
}

t_float4 mult_vec_matrix(t_float4 in, t_m44 m)
{
	t_float4 out;

	out.x = in.x * m.m[0][0] + in.y * m.m[1][0] + in.z * m.m[2][0] + in.w * m.m[3][0];
	out.y = in.x * m.m[0][1] + in.y * m.m[1][1] + in.z * m.m[2][1] + in.w * m.m[3][1];
	out.z = in.x * m.m[0][2] + in.y * m.m[1][2] + in.z * m.m[2][2] + in.w * m.m[3][2];
	out.w = in.x * m.m[0][3] + in.y * m.m[1][3] + in.z * m.m[2][3] + in.w * m.m[3][3];
	return out;
}

t_m44 mult_matrix(t_m44 lhs, t_m44 rhs)
{
	t_m44			result;
	uint_fast8_t	i;

	i = -1;
	while (++i < 4)
		result.m[i] = mult_vec_matrix(lhs.m[i], rhs);
	return result;
}
