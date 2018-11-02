/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectorpopfront.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 16:10:00 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/08 20:48:51 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_vec_popfront(t_vector *vect)
{
	if (vect->front == vect->back)
		return (NULL);
	return (ft_vec_get(vect, vect->front++));
}
