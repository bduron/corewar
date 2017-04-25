/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 18:17:08 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/04 18:18:43 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

void	*ft_memdup(const void *src, size_t size)
{
	size_t		i;
	void		*cpy;
	const char	*src_char;
	char		*cpy_char;

	i = 0;
	cpy = malloc(size);
	src_char = src;
	cpy_char = cpy;
	if (cpy != NULL)
	{
		while (i < size)
		{
			cpy_char[i] = src_char[i];
			i++;
		}
		return (cpy);
	}
	else
		return (NULL);
}
