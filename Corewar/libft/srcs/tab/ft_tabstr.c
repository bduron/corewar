/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 15:16:15 by kcosta            #+#    #+#             */
/*   Updated: 2017/02/18 15:16:24 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tab.h"
#include "ft_string.h"

char		**ft_tabstr(char **tab, char *entry)
{
	while (*tab)
	{
		if (!ft_strncmp(*tab, entry, ft_strlen(entry)))
			return (tab);
		tab++;
	}
	return (NULL);
}
