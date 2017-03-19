/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 16:31:35 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 15:16:12 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	char	*ptrstr;

	if (!(str = (char*)malloc(sizeof(char) * size + 1)))
		return (NULL);
	ptrstr = str;
	while (size + 1)
	{
		*ptrstr = 0;
		ptrstr++;
		size--;
	}
	return (str);
}
