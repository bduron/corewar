/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:31:25 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:24 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *alst)
{
	int size;

	if (alst)
	{
		size = 1;
		while (alst->next)
		{
			size++;
			alst = alst->next;
		}
		return (size);
	}
	else
		return (0);
}
