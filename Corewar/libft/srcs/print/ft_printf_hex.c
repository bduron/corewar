/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:19:47 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/01 13:29:29 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include "ft_ctype.h"

static size_t	ft_count_digit(uintmax_t nb, t_format *format)
{
	size_t	digits;

	if (!nb)
	{
		if (format)
			if (format->precision == 0)
				return (0);
		return (1);
	}
	if (format)
		digits = 2 * (format->flags.hash && format->type != 'p');
	else
		digits = 0;
	while (nb != 0)
	{
		digits++;
		nb /= 16;
	}
	return (digits);
}

static void		ft_putnbr_printf(uintmax_t nb, t_format *format)
{
	int			digit;
	uintmax_t	power;

	digit = ft_count_digit(nb, NULL);
	power = 1;
	if (format->precision == 0)
		return ;
	while (--digit > 0)
		power *= 16;
	while (power > 0)
	{
		if (format->type == 'X')
			ft_putchar(ft_toupper(HEX[nb / power]));
		else
			ft_putchar(HEX[nb / power]);
		nb %= power;
		power /= 16;
	}
}

static void		ft_print_alter(uintmax_t nb, t_format *format, size_t *size)
{
	if (format->flags.hash && nb != 0)
	{
		ft_putchar('0');
		ft_putchar(format->type);
		*size = *size - 2;
		format->flags.hash = !format->flags.hash;
	}
	if (format->flags.minus)
	{
		if (format->precision != -1)
		{
			while ((size_t)format->precision > *size)
			{
				ft_putchar('0');
				(*size)++;
			}
		}
		ft_putnbr_printf(nb, format);
	}
}

int				ft_printf_hex(uintmax_t nb, t_format *format)
{
	size_t	size;
	size_t	dup;

	size = ft_count_digit(nb, format);
	format->precision = (format->precision < (int)size && format->flags.hash) ?
														-1 : format->precision;
	dup = (format->precision > (int)size) ? format->precision : size;
	dup = (nb > 0 && format->flags.hash && format->precision != -1) ?
																dup + 2 : dup;
	if (format->flags.minus)
	{
		ft_print_alter(nb, format, &size);
		while ((size_t)format->width > dup++)
			ft_putchar(' ');
	}
	else
	{
		if (format->flags.zero && format->precision == -1)
			ft_print_alter(nb, format, &size);
		while ((size_t)format->width > dup++)
			ft_putchar((format->flags.zero) ? '0' : ' ');
		format->flags.minus = 1;
		ft_print_alter(nb, format, &size);
	}
	return (dup - 1);
}

int				ft_printf_print_hex(va_list ap, t_format *format)
{
	if (format->type == 'p')
		return (ft_printf_print_address(ap, format));
	if (format->length == L_HH)
		return (ft_printf_hex((unsigned char)va_arg(ap, int), format));
	else if (format->length == L_H)
		return (ft_printf_hex((unsigned short)va_arg(ap, int), format));
	else if (format->length == L_L)
		return (ft_printf_hex(va_arg(ap, unsigned long), format));
	else if (format->length == L_LL)
		return (ft_printf_hex(va_arg(ap, unsigned long long), format));
	else if (format->length == L_J)
		return (ft_printf_hex(va_arg(ap, uintmax_t), format));
	else if (format->length == L_Z)
		return (ft_printf_hex(va_arg(ap, size_t), format));
	else
		return (ft_printf_hex(va_arg(ap, unsigned int), format));
}
