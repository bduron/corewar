/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:05:16 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 15:22:30 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	char	*map;
	char	*ptrmap;

	if (!s)
		return (NULL);
	if (!(map = ft_strnew(ft_strlen(s))))
		return (NULL);
	ptrmap = map;
	while (*s)
		*(ptrmap++) = f(*(s++));
	*ptrmap = 0;
	return (map);
}
