/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectorpushback.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:32:57 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/08 20:49:02 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_vec_pushback(t_vector *vector, const void *content)
{
	void	*result;

	result = ft_vec_set(vector, vector->back, content);
	vector->back++;
	return result;
}
