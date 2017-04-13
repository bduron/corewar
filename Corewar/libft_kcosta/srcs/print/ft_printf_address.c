/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_address.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 17:54:42 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 18:06:04 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

static	void	ft_printf_zero(t_format *format, size_t size)
{
	if (format->flags.minus || !format->flags.zero)
		ft_putnstr("0x", 2);
	if (format->precision != -1)
	{
		size = ((int)size - 2 > 0) ? size - 2 : 0;
		while ((size_t)format->precision > size++)
			ft_putchar('0');
	}
	else
		ft_putchar('0');
}

static int		ft_printf_alter(t_format *format)
{
	size_t	size;
	size_t	dup;

	size = 2;
	dup = (format->precision != -1) ?
								size + format->precision : size + 1;
	if (format->flags.minus)
	{
		ft_printf_zero(format, size);
		while ((size_t)format->width > dup++)
			ft_putchar(' ');
	}
	else
	{
		if (format->flags.zero)
			ft_putnstr("0x", 2);
		while ((size_t)format->width > dup++)
			ft_putchar((format->flags.zero) ? '0' : ' ');
		ft_printf_zero(format, size);
	}
	return (dup - 1);
}

static int		ft_printf_address(size_t addr, t_format *format)
{
	if (addr)
	{
		format->flags.hash = 1;
		format->type = 'x';
		return (ft_printf_hex(addr, format));
	}
	else
		return (ft_printf_alter(format));
}

int				ft_printf_print_address(va_list ap, t_format *format)
{
	if (format->length == L_L)
	{
		format->flags.hash = 1;
		format->type = 'x';
		return (ft_printf_print_hex(ap, format));
	}
	else
		return (ft_printf_address((size_t)va_arg(ap, void *), format));
}
