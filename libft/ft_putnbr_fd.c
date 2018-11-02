/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:08:59 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:17 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	int	delim;

	delim = 1000000000;
	if (nb < 0)
		ft_putchar_fd('-', fd);
	if (nb == 0)
	{
		ft_putstr_fd("0", fd);
		return ;
	}
	while (delim && !(nb / delim))
		delim /= 10;
	while (delim)
	{
		ft_putchar_fd((nb < 0 ? -(nb / delim) : nb / delim) + '0', fd);
		nb %= delim;
		delim /= 10;
	}
}
