/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_writer_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolrajht <wolrajht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 13:16:25 by wolrajht          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:57 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			write_x(t_directive *d, va_list cpy)
{
	int		fig;
	int		len;
	char	*str;
	char	prefix;

	fig = set_ustr(d, &str, cpy);
	if (*str == '0' && !d->p)
		fig = 0;
	len = (d->p < fig) ? fig : d->p;
	if ((prefix = fig * (*str != '0') * d->af))
		len += 2;
	if (len < d->fl && !d->la && (!d->zp || d->p_arg))
		write_loop(' ', d->fl - len);
	if (prefix && d->cs == 'x')
		write(1, "0x", 2);
	else if (prefix && d->cs == 'X')
		write(1, "0X", 2);
	if (len < d->fl && !d->la && (d->zp && !d->p_arg))
		write_loop('0', d->fl - len);
	write_loop('0', d->p - fig);
	write(1, str, fig);
	free(str);
	if (len < d->fl && d->la)
		write_loop(' ', d->fl - len);
	return (len < d->fl ? d->fl : len);
}

int			write_u(t_directive *d, va_list cpy)
{
	int		fig;
	int		len;
	char	*str;

	fig = set_ustr(d, &str, cpy);
	if (*str == '0' && !d->p)
		fig = 0;
	len = (d->p < fig) ? fig : d->p;
	if (len < d->fl && !d->la && (!d->zp || d->p_arg))
		write_loop(' ', d->fl - len);
	if (len < d->fl && !d->la && (d->zp && !d->p_arg))
		write_loop('0', d->fl - len);
	write_loop('0', d->p - fig);
	write(1, str, fig);
	free(str);
	if (len < d->fl && d->la)
		write_loop(' ', d->fl - len);
	return (len < d->fl ? d->fl : len);
}

int			write_ob(t_directive *d, va_list cpy)
{
	int		fig;
	int		len;
	char	*str;
	char	prefix;

	fig = set_ustr(d, &str, cpy);
	if (*str == '0' && !d->p)
		fig = 0;
	len = (d->p < fig) ? fig : d->p;
	if ((prefix = (!fig || (*str != '0' && d->p <= fig)) * d->af))
		++len;
	if (len < d->fl && !d->la && (!d->zp || d->p_arg))
		write_loop(' ', d->fl - len);
	if (prefix)
		write(1, "0", 1);
	if (len < d->fl && !d->la && (d->zp && !d->p_arg))
		write_loop('0', d->fl - len);
	write_loop('0', d->p - fig);
	write(1, str, fig);
	free(str);
	if (len < d->fl && d->la)
		write_loop(' ', d->fl - len);
	return (len < d->fl ? d->fl : len);
}
