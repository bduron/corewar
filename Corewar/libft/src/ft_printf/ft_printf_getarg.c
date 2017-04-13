/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_getarg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 12:28:16 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:21:54 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	get_arg(t_flags *f)
{
	if (f->mod['z'])
		return (va_arg(f->ap, size_t));
	if (f->mod['j'])
		return (va_arg(f->ap, intmax_t));
	if (f->mod['L'])
		return (va_arg(f->ap, long long));
	if (f->mod['l'])
		return (va_arg(f->ap, long));
	if (f->mod['h'])
		return ((short)va_arg(f->ap, int));
	if (f->mod['H'])
		return ((signed char)va_arg(f->ap, int));
	return (va_arg(f->ap, int));
}

long long	get_arg_u(t_flags *f)
{
	if (f->mod['z'])
		return (va_arg(f->ap, size_t));
	if (f->mod['j'])
		return (va_arg(f->ap, uintmax_t));
	if (f->mod['L'])
		return (va_arg(f->ap, unsigned long long));
	if (f->mod['l'])
	{
		if (f->id == 'c')
			return (va_arg(f->ap, wchar_t));
		else
			return (va_arg(f->ap, unsigned long));
	}
	if (f->mod['h'])
		return ((unsigned short)va_arg(f->ap, unsigned int));
	if (f->mod['H'])
		return ((unsigned char)va_arg(f->ap, unsigned int));
	return (va_arg(f->ap, unsigned int));
}
