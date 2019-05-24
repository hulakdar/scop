#include "math.h"
#include "libft.h"

t_float2 perspective_top_right(float angle_of_view, float imageAspectRatio, float near)
{
	float		right;
	t_float2	tr;

	const float top = tanf(angle_of_view * 0.5 * M_PI / 180) * near;
	right = imageAspectRatio * top;
	tr[0] = top;
	tr[1] = right;
	return tr;
}

t_m44	m_world()
{
	return (t_m44) {.m = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,-3.5,1}
	}};
}

t_m44	m_model(t_float2 angles, t_float4 position, float scale)
{
	const t_m44 y_axis = { .m = {
		{cosf(angles.y),	0,	-sinf(angles.y),0},
		{0,					1,	0,				0},
		{sinf(angles.y),	0,	cosf(angles.y),	0},
		{0,0,0,1}
	} };
	const t_m44 x_axis = { .m = {
		{1,	0,					0,				0},
		{0,	cosf(angles.x),		sinf(angles.x),	0},
		{0,	-sinf(angles.x),	cosf(angles.x),	0},
		{0,0,0,1}
	} };
	const t_m44 offset = { .m = {
		{1,	0,	0,	0},
		{0,	1,	0,	0},
		{0,	0,	1,	0},
		position
	} };
	const t_m44 scaling = { .m = {
		{scale,	0,				0,		0},
		{0,		scale,			0,		0},
		{0,		0,				scale,	0},
		{0,0,0,1}
	} };
	const t_m44 result = mult_matrix(
			mult_matrix(
				offset,
				scaling
			),
			mult_matrix(
				y_axis,
				x_axis
			)
		);

	return (result);
}

__attribute__((noinline))
t_m44	frustum(t_float2 tr, float n, float f)
{
	const float t = tr[0];
	const float r = tr[1];
	const float	b = -r;
	const float	l = -t;
	t_m44		M;

	ft_bzero(&M, sizeof(t_m44));
	M.m[0][0] = 2 * n / (r - l);
	M.m[1][1] = 2 * n / (t - b);
	M.m[2][0] = (r + l) / (r - l);
	M.m[2][1] = (t + b) / (t - b);
	M.m[2][2] = -(f + n) / (f - n);
	M.m[2][3] = -1;
	M.m[3][2] = -2 * f * n / (f - n);
	return M;
}

t_float4 cross_product(t_float4 lhs, t_float4 rhs)
{
	return (t_float4) {
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x,
		0
	};
}

t_float4 normalize(t_float4 v)
{
	float		length;
	t_float4	squared;

	squared = v * v;
	length = squared.x + squared.y + squared.z;
	return v / sqrtf(length);
}
