/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:43:09 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 16:01:37 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	t_byte	*ptrs1;
	t_byte	*ptrs2;

	ptrs1 = (t_byte*)s1;
	ptrs2 = (t_byte*)s2;
	while (n > 0)
	{
		if (*ptrs1 != *ptrs2)
			return (*ptrs1 - *ptrs2);
		ptrs1++;
		ptrs2++;
		n--;
	}
	return (0);
}
