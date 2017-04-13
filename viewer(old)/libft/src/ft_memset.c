/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 09:55:52 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:40 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ucb;
	unsigned char	stride;
	size_t			i;

	ucb = (unsigned char *)b;
	stride = sizeof(unsigned char);
	i = 0;
	while (i < len)
		*(ucb + i++ * stride) = c;
	return (b);
}
