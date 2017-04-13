/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:12:56 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:39 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_cpy;
	const unsigned char	*src_cpy;
	unsigned char		*temp;
	size_t				i;

	dst_cpy = (unsigned char *)dst;
	src_cpy = (const unsigned char *)src;
	if (!(temp = (unsigned char *)malloc(len * sizeof(unsigned char))))
		return (dst);
	i = -1;
	while (++i < len)
		temp[i] = src_cpy[i];
	i = -1;
	while (++i < len)
		dst_cpy[i] = temp[i];
	free(temp);
	return (dst);
}
