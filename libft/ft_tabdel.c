/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 16:28:54 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:22:33 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabdel(char ***hint)
{
	char	**tab;
	size_t	cunt;

	tab = *hint;
	cunt = 0;
	while (tab[cunt])
	{
		free(tab[cunt]);
		cunt++;
	}
	free(tab);
}
