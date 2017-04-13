/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_writer_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolrajht <wolrajht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 13:16:25 by wolrajht          #+#    #+#             */
/*   Updated: 2017/03/01 17:20:27 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		write_p(t_directive *d, va_list cpy)
{
	int		fig;
	int		len;
	char	*str;

	fig = set_ustr(d, &str, cpy);
	if (*str == '0' && !d->p)
		fig = 0;
	len = (d->p < fig) ? fig + 2 : d->p + 2;
	if (len < d->fl && !d->la && (!d->zp || d->p_arg))
		write_loop(' ', d->fl - len);
	write(1, "0x", 2);
	if (len < d->fl && !d->la && (d->zp && !d->p_arg))
		write_loop('0', d->fl - len);
	write_loop('0', d->p - fig);
	write(1, str, fig);
	free(str);
	if (len < d->fl && d->la)
		write_loop(' ', d->fl - len);
	return (len < d->fl ? d->fl : len);
}

int		write_c(t_directive *d, va_list cpy)
{
	char	mb[6];
	wchar_t	wc;
	int		len;

	if (d->lm == 'l')
		wc = (wint_t)get_number(cpy, d->na);
	else
		wc = (char)get_number(cpy, d->na);
	if (!d->la)
		write_loop(d->zp ? '0' : ' ', d->fl - 1);
	len = ft_wctomb(mb, wc);
	write(1, mb, len);
	if (d->la)
		write_loop(' ', d->fl - 1);
	return (len < d->fl ? d->fl : len);
}

int		write_s(t_directive *d, va_list cpy)
{
	char	*str;
	int		len;

	str = (char *)get_number(cpy, d->na);
	str = (!str) ? "(null)" : str;
	len = -1;
	while (str[++len])
		;
	if (d->p_arg && d->p < len)
		len = d->p;
	if (!d->la)
		write_loop(d->zp ? '0' : ' ', d->fl - len);
	write(1, str, len);
	if (d->la)
		write_loop(' ', d->fl - len);
	return (len < d->fl ? d->fl : len);
}

int		write_error(t_directive *d)
{
	int	len;

	len = (d->cs) ? 1 : 0;
	if (!d->la)
		write_loop(d->zp ? '0' : ' ', d->fl - len);
	write(1, &(d->cs), len);
	if (d->la)
		write_loop(' ', d->fl - len);
	return (len < d->fl ? d->fl : len);
}
