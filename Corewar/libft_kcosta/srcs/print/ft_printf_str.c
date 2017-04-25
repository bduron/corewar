/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 21:49:50 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 18:09:22 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include "ft_string.h"

static int		ft_wstrlen(wchar_t *str, t_format *format)
{
	size_t	len;
	int		tmp;
	int		precision;

	len = 0;
	precision = format->precision;
	while (*str)
	{
		if ((tmp = ft_wcharlen(*str)) == -1)
			return (-1);
		if (precision != -1)
		{
			if (precision - tmp >= 0)
			{
				len += tmp;
				precision -= tmp;
			}
			else
				return (len);
		}
		else
			len += tmp;
		str++;
	}
	return (len);
}

static int		ft_putnwstr(wchar_t *str, size_t len)
{
	size_t	ret;
	int		char_len;

	ret = len;
	if (!str)
		return (0);
	while (len && *str)
	{
		char_len = ft_wcharlen(*str);
		if ((int)len - char_len >= 0)
			ft_putwchar(*str++);
		len = ((int)len - char_len > 0) ? len - char_len : 0;
	}
	return (ret);
}

static int		ft_printf_wstr(wchar_t *str, t_format *format)
{
	int		size;
	size_t	dup;

	if (!str)
		str = L"(null)";
	if ((size = ft_wstrlen(str, format)) == -1)
		return (-1);
	dup = size;
	if (format->flags.minus)
	{
		ft_putnwstr(str, dup);
		while (format->width > size++)
			ft_putchar(' ');
	}
	else
	{
		while (format->width > size++)
			ft_putchar((format->flags.zero) ? '0' : ' ');
		ft_putnwstr(str, dup);
	}
	return (size - 1);
}

static int		ft_printf_str(char *str, t_format *format)
{
	size_t	size;
	size_t	dup;

	if (!str)
		str = "(null)";
	size = ft_strlen(str);
	size = ((size_t)format->precision < size) ? format->precision : size;
	dup = size;
	if (format->flags.minus)
	{
		ft_putnstr(str, dup);
		while ((size_t)format->width > size++)
			ft_putchar(' ');
	}
	else
	{
		while ((size_t)format->width > size++)
			ft_putchar((format->flags.zero) ? '0' : ' ');
		ft_putnstr(str, dup);
	}
	return (size - 1);
}

int				ft_printf_print_str(va_list ap, t_format *format)
{
	if (format->type == 'S')
		format->length = L_L;
	if (format->length == L_L)
		return (ft_printf_wstr(va_arg(ap, wchar_t*), format));
	else
		return (ft_printf_str(va_arg(ap, char*), format));
}
