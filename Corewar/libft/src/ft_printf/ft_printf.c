/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:08:20 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:20:44 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	t_flags f;

	f.plen = 0;
	va_start(f.ap, format);
	fmt(&f, format);
	va_end(f.ap);
	return (f.plen);
}

void	fmt(t_flags *f, const char *format)
{
	char *s;

	s = (char *)format;
	reset_flags(f);
	while (*s)
	{
		if (*s != '%')
		{
			ft_putchar(*s);
			f->plen++;
		}
		else
		{
			s = get_flags(s, f);
			launch_conv(f);
			reset_flags(f);
		}
		s++;
	}
}
