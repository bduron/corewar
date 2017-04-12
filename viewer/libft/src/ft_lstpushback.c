/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:31:14 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:18 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushback(t_list **alst, void const *content, size_t content_size)
{
	if (*alst)
		if ((*alst)->next)
			ft_lstpushback(&(*alst)->next, content, content_size);
		else
			(*alst)->next = ft_lstnew(content, content_size);
	else
		*alst = ft_lstnew(content, content_size);
}
