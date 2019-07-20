/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectorset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 19:14:36 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:24:35 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_vec_set(t_vector *vect, size_t index, const void *content)
{
	void		*newarr;
	size_t		new_size;
	size_t		size;

	if (!vect)
		return (NULL);
	size = vect->size_of_type;
	if (index > vect->last)
	{
		new_size = vect->last + 1;
		while (new_size < index + 2)
			new_size <<= 1;
		newarr = ft_memalloc(new_size * vect->size_of_type);
		if (vect->data)
		{
			ft_memmove(newarr, vect->data, (vect->last + 1) * vect->size_of_type);
			free(vect->data);
		}
		vect->data = newarr;
		vect->last = new_size - 1;
	}
	return (ft_memmove(vect->data + (size * index), content, size));
}
