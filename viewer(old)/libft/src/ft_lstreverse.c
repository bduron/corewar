/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreverse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:32:12 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:23 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstreverse(t_list **alst)
{
	t_list *tmp;
	t_list *next;

	tmp = 0;
	while (*alst)
	{
		next = (*alst)->next;
		(*alst)->next = tmp;
		tmp = *alst;
		(*alst) = next;
	}
	(*alst) = tmp;
}
