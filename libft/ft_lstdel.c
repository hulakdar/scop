/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:35:01 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:21:52 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*curr;
	t_list	*prev;

	curr = *alst;
	while (curr)
	{
		prev = curr;
		if (del)
			del(curr->content, curr->content_size);
		curr = curr->next;
		free(prev);
	}
	*alst = NULL;
}
