/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:40:22 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:21:57 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *curr;

	new = (t_list *)NULL;
	if (lst)
	{
		new = f(ft_lstnew(lst->content, lst->content_size));
		curr = new;
		lst = lst->next;
		while (lst)
		{
			curr->next = f(ft_lstnew(lst->content, lst->content_size));
			curr = curr->next;
			lst = lst->next;
		}
	}
	return (new);
}
