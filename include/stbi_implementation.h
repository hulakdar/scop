/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stbi_implementation.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 17:40:31 by skamoza           #+#    #+#             */
/*   Updated: 2019/10/19 17:40:32 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STBI_IMPLEMENTATION_H
# define STBI_IMPLEMENTATION_H
# define STB_IMAGE_IMPLEMENTATION
# include <stb_image.h>

typedef struct	s_texture_data
{
	uint8_t	*ptr;
	int		x;
	int		y;
}				t_texture_data;
#endif
