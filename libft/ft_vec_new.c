/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectornew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 19:16:02 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/08 15:23:34 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	ft_vec_new(size_t size, size_t init)
{
	t_vector	dynarr;

	ft_vec_init(&dynarr, size, init);
	return (dynarr);
}
