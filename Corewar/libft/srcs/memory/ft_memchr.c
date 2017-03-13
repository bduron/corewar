/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:09:46 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 16:01:23 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	t_byte	*ptrs;

	ptrs = (t_byte*)s;
	while (n > 0)
	{
		if (*ptrs == (t_byte)c)
			return (ptrs);
		ptrs++;
		n--;
	}
	return (NULL);
}
