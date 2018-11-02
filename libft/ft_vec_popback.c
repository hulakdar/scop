/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectorpopback.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:24:24 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/08 20:48:37 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_vec_popback(t_vector *vect)
{
	if (!vect->back)
		return (NULL);
	return (ft_vec_get(vect, --vect->back));
}
