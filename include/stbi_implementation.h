#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

typedef struct	s_texture_data
{
	uint8_t	*ptr;
	int		x;
	int		y;
}				t_texture_data;
