/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushfront.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:36:43 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:20 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushfront(t_list **alst, void const *content, size_t content_size)
{
	t_list *tmp;

	tmp = *alst;
	*alst = ft_lstnew(content, content_size);
	(*alst)->next = tmp;
}
