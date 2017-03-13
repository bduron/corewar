/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 15:15:40 by kcosta            #+#    #+#             */
/*   Updated: 2017/02/18 15:16:27 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tab.h"

size_t		ft_tablen(char **tab)
{
	size_t	size;
	size_t	index;

	size = 0;
	index = 0;
	while (tab[index])
	{
		if (*tab[index])
			size++;
		index++;
	}
	return (size);
}
