/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:25:20 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 15:24:03 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*map;
	char	*ptrmap;
	int		index;

	if (!s)
		return (NULL);
	if (!(map = ft_strnew(ft_strlen(s))))
		return (NULL);
	index = 0;
	ptrmap = map;
	while (*s)
		*(ptrmap++) = f(index++, *(s++));
	*ptrmap = 0;
	return (map);
}
