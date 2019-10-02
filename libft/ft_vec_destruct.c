/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectordestruct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:23:15 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/08 20:39:58 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vec_destruct(t_vector *ptr, void (*destructor)(void*))
{
	size_t		i;
	void		*content;

	i = 0;
	while (i < ptr->back)
	{
		if ((content = *(void **)(ptr->data + i * ptr->size_of_type)))
			destructor(content);
		i++;
	}
	ft_vec_del(ptr);
}
