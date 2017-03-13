/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 15:07:38 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 17:48:51 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include "ft_string.h"

int			ft_printf_print_arg(va_list ap, t_format *format, int *size)
{
	int		tmp;

	tmp = 0;
	if (format->type == '%')
		tmp = ft_printf_pourcent(format);
	else if (format->type == 'd' || format->type == 'i' || format->type == 'D')
		tmp = ft_printf_print_num(ap, format);
	else if (format->type == 'u' || format->type == 'U')
		tmp = ft_printf_print_unsigned(ap, format);
	else if (format->type == 'o' || format->type == 'O')
		tmp = ft_printf_print_octal(ap, format);
	else if (format->type == 'x' || format->type == 'X' || format->type == 'p')
		tmp = ft_printf_print_hex(ap, format);
	else if (format->type == 's' || format->type == 'S')
		tmp = ft_printf_print_str(ap, format);
	else if (format->type == 'c' || format->type == 'C')
		tmp = ft_printf_print_char(ap, format);
	else
		return (-1);
	if (tmp == -1)
		return (-1);
	*size += tmp;
	return (1);
}

static int	ft_asprintf(va_list ap, const char **format, int *size)
{
	const char	*tmp;
	int			ret;

	tmp = *format;
	while (**format)
	{
		if (**format == '%')
		{
			*size = *size + ft_putnstr(tmp, (size_t)(*format - tmp));
			ret = ft_printf_format(ap, format, size);
			if (ret == -1)
				return (-1);
			else if (ret)
				*format = *format + 1;
			tmp = *format;
		}
		else
			*format = *format + 1;
	}
	if (*format != tmp)
		*size = *size + ft_putnstr(tmp, (size_t)(*format - tmp));
	return (1);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	int			size;

	size = 0;
	va_start(ap, format);
	if (ft_asprintf(ap, &format, &size) == -1)
	{
		va_end(ap);
		return (-1);
	}
	va_end(ap);
	return (size);
}
