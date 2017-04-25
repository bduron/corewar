/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 23:12:02 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 18:05:22 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

int			ft_wcharlen(wint_t c)
{
	if (c < 0 || c > 1114111)
		return (-1);
	else if (c <= 127)
		return (1);
	else if (c <= 2047)
		return (2);
	else if (c <= 55295 || (c >= 57344 && c <= 65535))
		return (3);
	else if (c <= 1114111)
		return (4);
	return (-1);
}

void		ft_putwchar(wint_t c)
{
	if (c < 0 || c > 1114111)
		return ;
	else if (c <= 127)
		ft_putchar(c);
	else if (c <= 2047)
	{
		ft_putchar((c >> 6) + 0xC0);
		ft_putchar((c & 0x3F) + 0x80);
	}
	else if (c <= 55295 || (c >= 57344 && c <= 65535))
	{
		ft_putchar((c >> 12) + 0xE0);
		ft_putchar(((c >> 6) & 0x3F) + 0x80);
		ft_putchar((c & 0x3F) + 0x80);
	}
	else if (c <= 1114111)
	{
		ft_putchar((c >> 18) + 0xF0);
		ft_putchar(((c >> 12) & 0x3F) + 0x80);
		ft_putchar(((c >> 6) & 0x3F) + 0x80);
		ft_putchar((c & 0x3F) + 0x80);
	}
}

static int	ft_printf_wchar(wchar_t c, t_format *format)
{
	size_t	size;

	size = 0;
	if (format->flags.minus)
	{
		size += ft_wcharlen(c);
		ft_putwchar(c);
		while ((size_t)format->width > size++)
			ft_putchar(' ');
	}
	else
	{
		while ((size_t)format->width > size++)
			ft_putchar(' ');
		size += ft_wcharlen(c);
		ft_putwchar(c);
	}
	return (size - 1);
}

static int	ft_printf_char(char c, t_format *format)
{
	size_t	size;

	size = 1;
	if (format->flags.minus)
	{
		ft_putchar(c);
		while ((size_t)format->width > size++)
			ft_putchar(' ');
	}
	else
	{
		while ((size_t)format->width > size++)
			ft_putchar((format->flags.zero) ? '0' : ' ');
		ft_putchar(c);
	}
	return (size - 1);
}

int			ft_printf_print_char(va_list ap, t_format *format)
{
	if (format->type == 'C')
		format->length = L_L;
	if (format->length == L_L)
		return ((ft_printf_wchar((wchar_t)va_arg(ap, wint_t), format)));
	else
		return ((ft_printf_char((char)va_arg(ap, int), format)));
}
