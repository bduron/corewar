/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 16:40:03 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/08 16:44:35 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strrstr(const char *big, const char *little)
{
	int		i;
	int		end;

	if (!*little)
		return ((char*)big);
	end = ft_strlen(big) - 1;
	while (end)
	{
		if (big[end] == *little)
		{
			i = 0;
			while (big[end + i] && little[i] && big[end + i] == little[i])
				i++;
			if (!little[i])
				return ((char*)&big[end]);
		}
		end--;
	}
	return (NULL);
}
