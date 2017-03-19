/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:42:16 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 15:14:37 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strstr(const char *big, const char *little)
{
	int		i;

	if (!*little)
		return ((char*)big);
	while (*big)
	{
		if (*big == *little)
		{
			i = 0;
			while (big[i] && little[i] && big[i] == little[i])
				i++;
			if (!little[i])
				return ((char*)big);
		}
		big++;
	}
	return (NULL);
}
