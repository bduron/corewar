/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:31:25 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/03 17:31:55 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstremif_sub(t_list **begin_list, t_list **current,
				t_list **prev, void (*del)(void *, size_t))
{
	if (*current == *prev)
	{
		(*del)((*prev)->content, (*prev)->content_size);
		*current = (*current)->next;
		free(*prev);
		*prev = *current;
		*begin_list = *current;
	}
	else
	{
		(*prev)->next = (*current)->next;
		(*del)((*current)->content, (*current)->content_size);
		free(*current);
		*current = (*prev)->next;
	}
}

void		ft_lstremif(t_list **begin_list, void *content_ref, int (*cmp)(),
				void (*del)(void *, size_t))
{
	t_list *prev;
	t_list *current;

	current = *begin_list;
	prev = current;
	while (current)
		if (!(*cmp)(current->content, content_ref))
		{
			ft_lstremif_sub(begin_list, &current, &prev, del);
		}
		else
		{
			prev = current;
			current = current->next;
		}
}
