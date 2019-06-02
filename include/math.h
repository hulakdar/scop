#pragma once

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

#if _MSC_VER
# include <corecrt_math.h>
#else
# include <math.h>
#endif

# define SQUARE(x) (x * x)

#if __INTELLISENSE__
typedef struct { float x; float y; } t_float2;
typedef struct { float x; float y; float z; float w; } t_float4;
typedef struct { t_float4 val[2]; } t_float8;
typedef struct { t_float4 val[4]; } t_float16;
typedef struct { int val[4]; } t_int4;
#define TO_FLOAT_VEC4(x)	__builtin_convertvector((x), t_float4)
#define SELECT(a, b, mask)	a;
#else
typedef float t_float16 __attribute__((ext_vector_type(16)));
typedef float t_float8 __attribute__((ext_vector_type(8)));
typedef float t_float4 __attribute__((ext_vector_type(4)));
typedef float t_float2 __attribute__((ext_vector_type(2)));
typedef int t_int4 __attribute__((ext_vector_type(4)));
#define TO_FLOAT_VEC4(x)	__builtin_convertvector((x), t_float4)
#define SELECT(a, b, mask)	((b) * (-mask) + (a) * ( 1 - (-mask)))
#endif

typedef struct	s_vertex 
{
	t_float4		position;
	t_float4		normal;
	t_float2		uv;
}				t_vertex;

typedef struct	s_m44
{
	union 
	{
	t_float4	m[4];
	t_float8	half[2];
	t_float16	val;
	};
}				t_m44;

t_float2	perspective_top_right(float angle_of_view, float imageAspectRatio, float n);
t_m44		frustum(t_float2 tr, float n, float f);
t_float4	mult_vec_matrix(t_float4 in, t_m44 m);
t_m44		mult_matrix(t_m44 lhs, t_m44 rhs);
t_float4	cross_product(t_float4 lhs, t_float4 rhs);
t_float4	normalize(t_float4 v);
t_m44		m_identity();
t_m44		m_look_at(t_float4 from, t_float4 to);
t_m44		m_model(t_float2 angles, t_float4 position, float scale);
t_m44		m_world();

