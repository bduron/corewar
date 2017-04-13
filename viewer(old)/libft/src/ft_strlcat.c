/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:21:20 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:46:18 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int len_src;
	unsigned int occupied;
	unsigned int to_cat;
	unsigned int i;
	unsigned int j;

	len_src = ft_strlen(src);
	to_cat = size;
	i = 0;
	j = 0;
	while (dst[i] != '\0' && to_cat-- > 0)
		i++;
	occupied = i;
	to_cat = size - occupied;
	if (to_cat == 0)
		return (occupied + len_src);
	while (src[j] != '\0' && to_cat-- > 1)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (occupied + len_src);
}
