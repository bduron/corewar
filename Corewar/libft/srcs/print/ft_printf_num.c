/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:58:42 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/01 13:24:21 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

static size_t	ft_count_digit(intmax_t nb, t_format *format)
{
	size_t	digits;

	if (!nb)
	{
		if (format)
			if (format->precision == 0)
				return (0);
	}
	if (format)
		digits = (nb == 0) +
				((format->flags.space) + (format->flags.plus)) | (nb < 0);
	else
		digits = 0;
	while (nb != 0)
	{
		digits++;
		nb /= 10;
	}
	return (digits);
}

static void		ft_putnbr_printf(intmax_t nb, t_format *format)
{
	int			digits;
	intmax_t	power;

	digits = ft_count_digit(nb, NULL);
	power = 1;
	if (!nb && format->precision == 0)
		return ;
	while (--digits > 0)
		power *= 10;
	while (power > 0)
	{
		ft_putchar(((nb / power) > 0) ? nb / power + '0' :
										(nb / power) * -1 + '0');
		nb %= power;
		power /= 10;
	}
}

static void		ft_print_zero(intmax_t nb, t_format *format, size_t *size,
								char add)
{
	if (add && (format->flags.minus ||
				!(format->flags.zero && format->precision == -1)))
		ft_putchar(add);
	if (nb < 0)
		*size = *size - 1;
	else
		*size = *size - (format->flags.space) - (format->flags.plus);
	if (format->precision != -1)
	{
		while ((size_t)format->precision > *size)
		{
			ft_putchar('0');
			(*size)++;
		}
	}
	if (add)
		(*size)++;
	ft_putnbr_printf(nb, format);
}

static int		ft_printf_num(intmax_t nb, t_format *format, char add)
{
	size_t	size;
	size_t	dup;

	add = (nb < 0) ? '-' : add;
	size = ft_count_digit(nb, format);
	dup = (format->precision > (int)size) ?
							size + (format->precision - (int)size) : size;
	dup = (format->precision > 0) ?
		dup + ((format->flags.space) + (format->flags.plus)) | (nb < 0) : dup;
	if (format->flags.minus)
	{
		ft_print_zero(nb, format, &size, add);
		while ((size_t)format->width > dup++)
			ft_putchar(' ');
	}
	else
	{
		if (add && (format->flags.zero && format->precision == -1))
			ft_putchar(add);
		while ((size_t)format->width > dup++)
			ft_putchar((format->flags.zero && format->precision == -1) ?
																	'0' : ' ');
		ft_print_zero(nb, format, &size, add);
	}
	return ((format->width > (int)size) ? format->width : (int)size);
}

int				ft_printf_print_num(va_list ap, t_format *format)
{
	char	add;

	add = (format->flags.space) ? ' ' : 0;
	add = (format->flags.plus) ? '+' : add;
	if (format->type == 'D')
		format->length = L_L;
	if (format->length == L_HH)
		return (ft_printf_num((char)va_arg(ap, int), format, add));
	else if (format->length == L_H)
		return (ft_printf_num((short)va_arg(ap, int), format, add));
	else if (format->length == L_L)
		return (ft_printf_num(va_arg(ap, long), format, add));
	else if (format->length == L_LL)
		return (ft_printf_num(va_arg(ap, long long), format, add));
	else if (format->length == L_J)
		return (ft_printf_num(va_arg(ap, intmax_t), format, add));
	else if (format->length == L_Z)
		return (ft_printf_num(va_arg(ap, ssize_t), format, add));
	else
		return (ft_printf_num(va_arg(ap, int), format, add));
}
