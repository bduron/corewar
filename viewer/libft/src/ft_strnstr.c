/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 09:28:36 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:46:22 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;
	int		j;
	size_t	k;

	if (len < 1 || !*big)
		return (0);
	if (*little == '\0')
		return ((char *)(big));
	i = -1;
	while (big[++i] && len-- > 0)
	{
		j = -1;
		if (big[i] == little[0])
		{
			k = len + 1;
			while (little[++j] && k-- > 0)
				if (big[i + j] != little[j])
					break ;
			if (little[j] == '\0')
				return (char *)(big + i);
		}
	}
	return (0);
}
