/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectorinit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 13:31:48 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/08 16:10:42 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vec_init(t_vector *dynarr, size_t size, size_t init)
{
	size_t		new_size;

	new_size = 32;
	while (init * size > new_size)
		new_size = new_size << 1;
	dynarr->data = ft_memalloc(new_size * size);
	dynarr->last = new_size - 1;
	dynarr->size_of_type = size;
	dynarr->back = 0;
	dynarr->front = 0;
}
