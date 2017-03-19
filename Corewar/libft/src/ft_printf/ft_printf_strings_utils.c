/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_strings_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 15:31:58 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:58:51 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_wlen(wchar_t s)
{
	size_t len;

	len = 0;
	if (s <= 0x7F)
		len += 1;
	else if (s <= 0x7FF)
		len += 2;
	else if (s <= 0xFFFF)
		len += 3;
	else if (s <= 0x10FFFF)
		len += 4;
	return (len);
}

size_t	rem(size_t len, wchar_t *s)
{
	size_t	rem;
	int		i;

	rem = len;
	i = 0;
	while ((size_t)i < len && rem >= ft_wlen(s[i]))
		rem -= ft_wlen(s[i++]);
	return (rem);
}
