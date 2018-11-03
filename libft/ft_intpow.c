/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intpow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 16:42:36 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:20 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_intpow(unsigned base, unsigned power)
{
	size_t result;

	result = 1;
	while (power--)
		result *= base;
	return (result);
}
