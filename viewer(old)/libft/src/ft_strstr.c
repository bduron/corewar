/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 09:28:36 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:46:24 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int i;
	int j;

	if (*little == '\0')
		return ((char *)(big));
	i = 0;
	while (big[i])
	{
		j = 0;
		if (big[i] == little[j])
		{
			while (little[j])
			{
				if (big[i + j] != little[j])
					break ;
				j++;
			}
			if (little[j] == '\0')
				return (char *)(big + i);
		}
		i++;
	}
	return (0);
}
