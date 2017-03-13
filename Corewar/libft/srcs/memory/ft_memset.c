/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 19:18:53 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 15:54:57 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

void	*ft_memset(void *b, int c, size_t len)
{
	t_byte	*ptr;
	size_t	i;

	i = 0;
	ptr = (t_byte*)b;
	while (i < len)
	{
		*ptr = (t_byte)c;
		ptr++;
		i++;
	}
	return (b);
}
