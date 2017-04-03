/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumberstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 08:04:06 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/03 08:14:28 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumberstr(char *str)
{
	if (!*str)
		return (0);
	if ((*str == '-' || *str == '+') && !*(++str))
		return (0);
	while (*str)
	{
		if (*str < '0' || '9' < *str)
			return (0);
		++str;
	}
	return (1);
}
