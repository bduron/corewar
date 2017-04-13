/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:17:05 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:39:01 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_wildcards(t_flags *f, char *s)
{
	if (ft_isdigit(*s))
		f->width = ft_printf_atoi((const char*)s);
	while (ft_isdigit(*s))
		s++;
	if (*s == '*')
		f->width = (s++) ? va_arg(f->ap, int) : 0;
	if (f->width < 0)
	{
		f->flags['-']++;
		f->width = -f->width;
	}
	if (ft_isdigit(*s))
		f->width = ft_printf_atoi((const char*)s);
	while (ft_isdigit(*s))
		s++;
	if (*s == '.')
	{
		f->precision = (*++s == '*')
			? va_arg(f->ap, int) : ft_printf_atoi((const char*)s);
		f->flags['.']++;
		f->flags['.'] = f->precision < 0 && *s == '*' ? 0 : 1;
	}
	while (ft_isdigit(*s) || *s == '*')
		s++;
	return (s);
}
