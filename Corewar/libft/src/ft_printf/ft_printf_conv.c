/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:21:46 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:21:54 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	launch_conv(t_flags *f)
{
	launch_conv_digits(f);
	launch_conv_strings(f);
	launch_conv_unsigned(f);
}

void	launch_conv_digits(t_flags *f)
{
	if (f->id == 'o' || f->id == 'O' || is_x(f))
		f->flags[' '] = 0;
	(f->id == 'd' || f->id == 'i' || f->id == 'o' || is_x(f)) ? conv_d(f) : 0;
	if (f->id == 'D')
	{
		f->id = 'd';
		f->mod['l'] = 1;
		conv_d(f);
	}
}

void	launch_conv_strings(t_flags *f)
{
	if (f->id == 'C')
	{
		f->id = 'c';
		f->mod['l']++;
	}
	(f->id == 'c') ? put_c(f) : 0;
	if (f->id == 'O')
	{
		f->id = 'o';
		f->mod['l'] = 1;
		conv_d(f);
	}
	f->id == 'S' || (f->id == 's' && f->mod['l']) ? put_s_maj(f) : 0;
	f->id == 's' && !f->mod['l'] ? put_s(f) : 0;
}

void	launch_conv_unsigned(t_flags *f)
{
	if (f->id == 'b')
	{
		f->id = 'x';
		f->flags['b'] = 1;
		conv_d(f);
	}
	if (f->id == 'p')
	{
		f->id = 'x';
		f->flags['#'] = 1;
		f->flags['p'] = 1;
		f->flags[' '] = 0;
		f->mod['l'] = 1;
		conv_d(f);
	}
	if (f->id == 'u' || f->id == 'U')
	{
		f->mod['l'] = f->id == 'U' ? 1 : f->mod['l'];
		f->flags['#'] = 0;
		f->flags['+'] = 0;
		f->flags[' '] = 0;
		conv_u(f);
	}
	(isnt_id(f)) ? put_percent(f) : 0;
}
