/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 12:39:38 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 15:08:23 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strcpy(char *dst, const char *src)
{
	char	*ptrdst;

	ptrdst = dst;
	while (*src)
		*(ptrdst++) = *(src++);
	*ptrdst = *src;
	return (dst);
}
