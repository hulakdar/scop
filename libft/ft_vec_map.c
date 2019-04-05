/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_map.c		                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 16:10:00 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/08 20:48:51 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	ft_vec_map(t_vector *const vector,
	void (*function)(void *, void *const, void*), void *payload)
{
	size_t		i;
	size_t		offset;
	t_vector	result;

	i = 0;
	ft_vec_init(&result, vector->size_of_type, vector->last);
	while (i < vector->back)
	{
		offset = i++ * vector->size_of_type;
		function(&result.data[offset], &vector->data[offset], payload);
	}
}