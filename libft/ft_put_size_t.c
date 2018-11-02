/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_size_t.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <skamoza@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 21:09:31 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/09 21:16:13 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_size_t(size_t nb)
{
	size_t	delim;

	delim = 10000000000000000000UL;
	if (nb == 0)
	{
		ft_putstr("0");
		return ;
	}
	while (delim && !(nb / delim))
		delim /= 10;
	while (delim)
	{
		ft_putchar((char)(nb / delim + '0'));
		nb %= delim;
		delim /= 10;
	}
} 