/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectordel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 12:58:32 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/08 20:39:15 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vec_del(t_vector *vector)
{
	if (vector && vector->data)
	{
		free(vector->data);
		vector->data = NULL;
	}
}
