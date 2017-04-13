/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_loader.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolrajht <wolrajht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 13:16:25 by wolrajht          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:52 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				set_ustr(t_directive *d, char **str, va_list cpy)
{
	if (d->lm == 'H')
		return (ft_itoa_base(str,
			(unsigned char)get_number(cpy, d->na), d->base));
	else if (d->lm == 'h')
		return (ft_itoa_base(str,
			(unsigned short)get_number(cpy, d->na), d->base));
	else if (d->lm == 'l')
		return (ft_itoa_base(str,
			(unsigned long)get_number(cpy, d->na), d->base));
	else if (d->lm == 'L')
		return (ft_itoa_base(str, get_number(cpy, d->na), d->base));
	else if (d->lm == 'j')
		return (ft_itoa_base(str, (uintmax_t)get_number(cpy, d->na), d->base));
	else if (d->lm == 'z')
		return (ft_itoa_base(str, (size_t)get_number(cpy, d->na), d->base));
	else
		return (ft_itoa_base(str,
			(unsigned int)get_number(cpy, d->na), d->base));
}

size_t				set_str(t_directive *d, char **str, va_list cpy,
						char *is_negative)
{
	long long n;

	if (d->lm == 'H')
		n = (signed char)get_number(cpy, d->na);
	else if (d->lm == 'h')
		n = (short)get_number(cpy, d->na);
	else if (d->lm == 'l')
		n = (long)get_number(cpy, d->na);
	else if (d->lm == 'L')
		n = (long long)get_number(cpy, d->na);
	else if (d->lm == 'j')
		n = (intmax_t)get_number(cpy, d->na);
	else if (d->lm == 'z')
		n = (size_t)get_number(cpy, d->na);
	else
		n = (int)get_number(cpy, d->na);
	if (n < 0)
	{
		*is_negative = 1;
		return (ft_itoa_base(str, -n, d->base));
	}
	*is_negative = 0;
	return (ft_itoa_base(str, n, d->base));
}

unsigned long long	get_number(va_list cpy, int n)
{
	unsigned long long res;

	while (n--)
		res = va_arg(cpy, unsigned long long);
	return (res);
}
