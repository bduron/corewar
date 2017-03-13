/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:00:05 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 15:05:54 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*ptrdst;
	const char	*ptrsrc;
	size_t		len;
	size_t		i;

	ptrdst = dst;
	ptrsrc = src;
	i = size;
	while (i-- && *ptrdst)
		ptrdst++;
	len = ptrdst - dst;
	i = size - len;
	if (i == 0)
		return (len + ft_strlen(src));
	while (*ptrsrc)
	{
		if (i > 1)
		{
			*ptrdst++ = *ptrsrc;
			i--;
		}
		ptrsrc++;
	}
	*ptrdst = 0;
	return (len + (ptrsrc - src));
}
