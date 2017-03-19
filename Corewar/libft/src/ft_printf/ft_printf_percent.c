/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 11:23:49 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:21:54 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_percent(t_flags *f)
{
	wchar_t c;
	int		n;

	n = (f->width > 0) ? f->width : 1;
	c = (f->id == 'c') ? get_arg_u(f) : f->id;
	!f->flags['-'] && !f->flags['0'] ? pad(f->width - 1, ' ') : 0;
	f->flags['0'] && !f->flags['-'] ? pad(f->width - 1, '0') : 0;
	if (f->mod['l'])
	{
		(c > 127) ? f->plen += ft_putwchar(c) : 0;
		(c <= 127) ? ft_putchar(c) : 0;
	}
	else if (c)
		ft_putchar(c);
	f->flags['-'] ? pad(f->width - 1, ' ') : 0;
	f->plen += n;
}
