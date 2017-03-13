/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 15:54:26 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/14 15:58:21 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strremove(char **str, size_t index)
{
	char	*ret;

	if (!str || index > ft_strlen(*str))
		return (NULL);
	ret = ft_strnew(ft_strlen(*str) - 1);
	ret = ft_strncpy(ret, *str, index);
	ret[index - 1] = 0;
	ret = ft_strcat(ret, *str + index);
	ft_strdel(str);
	*str = ft_strdup(ret);
	ft_strdel(&ret);
	return (*str);
}
