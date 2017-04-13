/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 16:56:34 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/01 17:20:28 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		i_prev;
	int		printed;
	int		na;

	na = 1;
	i_prev = 0;
	printed = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
		if (format[i++] == '%')
		{
			if ((i - 1) - i_prev)
				printed += write(1, format + i_prev, (i - 1) - i_prev);
			printed += parse_directive(format, &i, args, &na);
			i_prev = i;
		}
	if (i - i_prev)
		printed += write(1, format + i_prev, i - i_prev);
	va_end(args);
	return (printed);
}
