/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:53:08 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:15 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *node;

	if (!(node = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content)
		if (!(node->content = ft_memalloc(content_size)))
			return (NULL);
		else
			node->content = ft_memcpy(node->content, content, content_size);
	else
		node->content = NULL;
	node->content_size = content_size;
	node->next = NULL;
	return (node);
}
