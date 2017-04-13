/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:53:10 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 15:14:55 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;

	if (!*little)
		return ((char*)big);
	while (*big && len)
	{
		if (*big == *little)
		{
			i = 0;
			while ((len - i) && big[i] && little[i] && big[i] == little[i])
				i++;
			if (!little[i])
				return ((char*)big);
		}
		big++;
		len--;
	}
	return (NULL);
}
