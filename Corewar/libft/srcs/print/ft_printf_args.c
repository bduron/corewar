/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 11:47:26 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 17:51:07 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include "ft_string.h"

static void		ft_initialise_format(t_format *format)
{
	format->flags.hash = 0;
	format->flags.zero = 0;
	format->flags.minus = 0;
	format->flags.plus = 0;
	format->flags.space = 0;
	format->length = -1;
}

static void		ft_get_flags(const char **str, t_format *format)
{
	while (ft_printf_isflag(**str))
	{
		if (**str == '#')
			format->flags.hash = 1;
		else if (**str == '0' && !format->flags.minus)
			format->flags.zero = 1;
		else if (**str == '-')
		{
			format->flags.minus = 1;
			format->flags.zero = 0;
		}
		else if (**str == '+')
		{
			format->flags.plus = 1;
			format->flags.space = 0;
		}
		else if (**str == ' ' && !format->flags.plus)
			format->flags.space = 1;
		(*str)++;
	}
}

static void		ft_get_length(const char **str, t_format *format)
{
	if (format->length < 1 && !ft_strncmp(*str, "h", 1))
	{
		if (!ft_strncmp(*str, "hh", 2))
			format->length = L_HH;
		else
			format->length = L_H;
	}
	format->length = (format->length < 2 && !ft_strncmp(*str, "l", 1)) ?
														L_L : format->length;
	format->length = (format->length < 3 && !ft_strncmp(*str, "ll", 2)) ?
														L_LL : format->length;
	format->length = (format->length < 4 && !ft_strncmp(*str, "j", 1)) ?
														L_J : format->length;
	format->length = (format->length < 5 && !ft_strncmp(*str, "z", 1)) ?
														L_Z : format->length;
	if (format->length == -1)
		return ;
	else if (format->length == 0 || format->length == 3)
		*str = (*str) + 2;
	else
		(*str)++;
}

int				ft_printf_format(va_list ap, const char **str, int *size)
{
	t_format	format;

	ft_initialise_format(&format);
	(*str)++;
	ft_get_flags(str, &format);
	ft_get_width(ap, str, &format);
	while (ft_printf_islength(**str))
		ft_get_length(str, &format);
	if (!ft_printf_istype(**str))
		ft_get_flags(str, &format);
	if (!ft_printf_istype(**str))
	{
		while (ft_printf_isflag(**str) || ft_printf_islength(**str) ||
				ft_printf_istype(**str))
			(*str)++;
		return (ft_printf_flush_format(str, &format, size));
	}
	format.type = **str;
	if (ft_printf_print_arg(ap, &format, size) == -1)
		return (-1);
	return (1);
}
