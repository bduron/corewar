/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 12:16:08 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:27 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*ucdst;
	const unsigned char	*ucsrc;
	size_t				i;

	ucdst = (unsigned char *)dst;
	ucsrc = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*ucdst = ucsrc[i++];
		if (*(ucdst++) == (unsigned char)c)
			return (dst + i);
	}
	return (0);
}
