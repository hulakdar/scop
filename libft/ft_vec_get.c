/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectorget.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 19:13:13 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:43 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_vec_get(t_vector *dynarr, size_t index)
{
	if (dynarr && dynarr->data && index <= dynarr->last)
		return (dynarr->data + (dynarr->size_of_type * index));
	return (NULL);
}
