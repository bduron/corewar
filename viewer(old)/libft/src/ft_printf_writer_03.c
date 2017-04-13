/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_writer_03.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolrajht <wolrajht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 13:16:25 by wolrajht          #+#    #+#             */
/*   Updated: 2017/03/01 17:20:27 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_di_sub(t_directive *d, char negative)
{
	if (negative)
		write(1, "-", 1);
	else if (d->as)
		write(1, "+", 1);
	else if (d->pa)
		write(1, " ", 1);
}

int			write_di(t_directive *d, va_list cpy)
{
	int		fig;
	int		len;
	char	*str;
	char	negative;

	negative = 0;
	fig = set_str(d, &str, cpy, &negative);
	if (*str == '0' && !d->p)
		fig = 0;
	len = (d->p < fig) ? fig : d->p;
	if (negative || d->as || d->pa)
		++len;
	if (len < d->fl && !d->la && (!d->zp || d->p_arg))
		write_loop(' ', d->fl - len);
	write_di_sub(d, negative);
	if (len < d->fl && !d->la && (d->zp && !d->p_arg))
		write_loop('0', d->fl - len);
	write_loop('0', d->p - fig);
	write(1, str, fig);
	free(str);
	if (len < d->fl && d->la)
		write_loop(' ', d->fl - len);
	return (len < d->fl ? d->fl : len);
}

static void	write_ls_sub(char mb[6], wchar_t *wstr, int len)
{
	int i;
	int ml;

	i = len;
	while (i > 0)
	{
		ml = ft_wctomb(mb, *wstr++);
		i -= ml;
		if (i >= 0)
			write(1, mb, ml);
	}
}

int			write_ls(t_directive *d, va_list cpy)
{
	char	mb[6];
	wchar_t	*wstr;
	int		i;
	int		len;
	int		ml;

	wstr = (wchar_t *)get_number(cpy, d->na);
	wstr = (!wstr) ? L"(null)" : wstr;
	len = 0;
	i = -1;
	while ((ml = ft_wctomb(mb, wstr[++i])))
	{
		if (!*mb || (d->p_arg && d->p < len + ml))
			break ;
		len += ml;
	}
	if (!d->la)
		write_loop(d->zp ? '0' : ' ', d->fl - len);
	write_ls_sub(mb, wstr, len);
	if (d->la)
		write_loop(' ', d->fl - len);
	return (len < d->fl ? d->fl : len);
}
