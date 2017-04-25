/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 16:23:54 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 16:01:04 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (!(mem = (void*)malloc(size)))
		return (NULL);
	mem = ft_memset(mem, 0, size);
	return (mem);
}
