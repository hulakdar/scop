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

void	ft_vec_destruct(t_vector *ptr)
{
	size_t		cunt;
	void		*content;

	if (!ptr)
		return ;
	cunt = 0;
	while (cunt < ptr->back)
	{
		if ((content = *(void **)(ptr->data + cunt * ptr->size_of_type)))
			free(content);
		cunt++;
	}
	ft_vec_del(ptr);
}
