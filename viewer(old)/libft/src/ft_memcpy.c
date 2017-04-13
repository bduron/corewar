/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 12:16:00 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:31 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*ucdst;
	const unsigned char	*ucsrc;

	ucdst = (unsigned char *)dst;
	ucsrc = (const unsigned char *)src;
	while (n-- > 0)
		*(ucdst++) = *(ucsrc++);
	return (dst);
}
