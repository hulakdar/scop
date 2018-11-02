/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:33:36 by skamoza           #+#    #+#             */
/*   Updated: 2017/12/05 12:21:59 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	new = ft_memalloc(sizeof(t_list));
	if (!new)
		return (NULL);
	if (content)
		new->content = ft_memalloc(content_size);
	else
		new->content = NULL;
	if (content && ft_memcpy(new->content, content, content_size))
		new->content_size = content_size;
	else
		new->content_size = 0;
	new->next = NULL;
	return (new);
}
