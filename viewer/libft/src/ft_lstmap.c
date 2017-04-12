/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 19:44:22 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:15 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *start;
	t_list *m;

	start = NULL;
	if (lst)
	{
		start = (*f)(lst);
		m = start;
		while (lst->next)
		{
			m->next = (*f)(lst->next);
			m = m->next;
			lst = lst->next;
		}
	}
	return (start);
}
