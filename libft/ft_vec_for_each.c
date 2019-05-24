/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_for_each.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 16:10:00 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/08 20:48:51 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_vec_for_each(t_vector *vector,
	t_for_each_predicate function, void *payload)
{
	size_t i;

	i = 0;
	while (i < vector->back)
		function(&vector->data[i++ * vector->size_of_type], payload);
}