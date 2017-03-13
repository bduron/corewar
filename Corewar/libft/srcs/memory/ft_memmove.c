/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 12:27:59 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 16:01:47 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	t_byte	*ptrdst;
	t_byte	*ptrsrc;

	ptrdst = (t_byte*)dst;
	ptrsrc = (t_byte*)src;
	if (dst < src)
		return (ft_memcpy(dst, src, len));
	while (len-- > 0)
		ptrdst[len] = ptrsrc[len];
	return (dst);
}
