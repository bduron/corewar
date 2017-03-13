/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 15:53:27 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/14 15:57:51 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strinsert(char **str, char c, size_t index)
{
	char	*ret;

	if (!str || index > ft_strlen(*str))
		return (NULL);
	ret = ft_strnew(ft_strlen(*str) + 1);
	ret = ft_strncpy(ret, *str, index);
	ret[index] = c;
	ret = ft_strcat(ret, *str + index);
	ft_strdel(str);
	*str = ft_strdup(ret);
	ft_strdel(&ret);
	return (*str);
}
