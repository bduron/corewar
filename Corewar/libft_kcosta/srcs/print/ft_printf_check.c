/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 12:17:40 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 17:52:39 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

int		ft_printf_isflag(int c)
{
	return (c == '#' || c == '0' || c == '-' || c == '+' || c == ' ');
}

int		ft_printf_islength(int c)
{
	return (c == 'h' || c == 'l' || c == 'j' || c == 'z');
}

int		ft_printf_istype(int c)
{
	return (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' ||
			c == 'i' || c == 'o' || c == 'O' || c == 'u' || c == 'U' ||
			c == 'x' || c == 'X' || c == 'c' || c == 'C' || c == '%');
}

int		ft_printf_flush_format(const char **str, t_format *format, int *size)
{
	size_t	dup;

	if (!**str)
		return (0);
	dup = 1;
	if (format->flags.minus)
	{
		ft_putchar(**str);
		while ((size_t)format->width > dup++)
			ft_putchar(' ');
	}
	else
	{
		while ((size_t)format->width > dup++)
			ft_putchar((format->flags.zero) ? '0' : ' ');
		ft_putchar(**str);
	}
	*size += (dup - 1);
	(*str)++;
	return (0);
}
