/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_octal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 12:13:35 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/01 13:26:05 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

static size_t	ft_count_digit(uintmax_t nb, t_format *format)
{
	size_t	digits;

	if (!nb)
	{
		if (format)
			if (format->precision == 0 ||
				(format->precision <= 0 && format->flags.hash))
				return (0);
		return (1);
	}
	if (format)
		digits = (format->flags.hash && format->precision <= 0);
	else
		digits = 0;
	while (nb != 0)
	{
		digits++;
		nb /= 8;
	}
	return (digits);
}

static void		ft_putnbr_printf(uintmax_t nb, t_format *format)
{
	int			digits;
	uintmax_t	power;

	digits = ft_count_digit(nb, NULL);
	power = 1;
	if ((!nb && format->precision == 0) ||
		(format->flags.hash && format->precision == -1 && !nb))
		return ;
	while (--digits > 0)
		power *= 8;
	while (power > 0)
	{
		ft_putchar(nb / power + '0');
		nb %= power;
		power /= 8;
	}
}

static void		ft_print_zero(t_format *format, size_t *size)
{
	if (format->precision > 0)
	{
		while ((size_t)format->precision > *size)
		{
			ft_putchar('0');
			(*size)++;
		}
	}
	else if (format->flags.hash)
	{
		ft_putchar('0');
		(*size)++;
	}
}

static int		ft_printf_octal(uintmax_t nb, t_format *format)
{
	size_t	size;
	size_t	dup;

	size = ft_count_digit(nb, format);
	dup = (format->precision > (int)size) ?
								size + (format->precision - (int)size) : size;
	if (format->flags.minus)
	{
		ft_print_zero(format, &size);
		ft_putnbr_printf(nb, format);
		while ((size_t)format->width > dup++)
			ft_putchar(' ');
	}
	else
	{
		while ((size_t)format->width > dup++)
			ft_putchar((format->flags.zero && format->precision == -1) ?
																	'0' : ' ');
		ft_print_zero(format, &size);
		ft_putnbr_printf(nb, format);
	}
	return (dup - (!(format->flags.hash && nb == 0)));
}

int				ft_printf_print_octal(va_list ap, t_format *format)
{
	if (format->type == 'O')
		format->length = L_L;
	if (format->length == L_HH)
		return (ft_printf_octal((unsigned char)va_arg(ap, int), format));
	else if (format->length == L_H)
		return (ft_printf_octal((unsigned short)va_arg(ap, int), format));
	else if (format->length == L_L)
		return (ft_printf_octal(va_arg(ap, unsigned long), format));
	else if (format->length == L_LL)
		return (ft_printf_octal(va_arg(ap, unsigned long long), format));
	else if (format->length == L_J)
		return (ft_printf_octal(va_arg(ap, uintmax_t), format));
	else if (format->length == L_Z)
		return (ft_printf_octal(va_arg(ap, size_t), format));
	else
		return (ft_printf_octal(va_arg(ap, unsigned int), format));
}
