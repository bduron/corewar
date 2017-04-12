/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_directive.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 15:08:08 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:41 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		write_directive(t_directive *d, va_list cpy)
{
	if (d->cs == 'p')
		return (write_p(d, cpy));
	else if (d->cs == 'x' || d->cs == 'X')
		return (write_x(d, cpy));
	else if (d->cs == 'u' || d->cs == 'U')
		return (write_u(d, cpy));
	else if (d->cs == 'd' || d->cs == 'D' || d->cs == 'i')
		return (write_di(d, cpy));
	else if (d->cs == 'o' || d->cs == 'O' || d->cs == 'b')
		return (write_ob(d, cpy));
	else if (d->cs == 'c' || d->cs == 'C')
		return (write_c(d, cpy));
	else if ((d->cs == 's' && d->lm == 'l') || d->cs == 'S')
		return (write_ls(d, cpy));
	else if (d->cs == 's')
		return (write_s(d, cpy));
	else
		return (write_error(d));
	return (0);
}

void	init_directive(t_directive *d, int *i, int *na)
{
	const static t_base dec = {"0123456789", 10};

	d->pos = *i - 1;
	d->len = 0;
	d->na = *na;
	d->na_arg = 0;
	d->af = 0;
	d->zp = 0;
	d->la = 0;
	d->as = 0;
	d->pa = 0;
	d->fl = 0;
	d->fl_arg = 0;
	d->p = 1;
	d->p_arg = 0;
	d->lm = 0;
	d->cs = 0;
	d->base = &dec;
	d->valid = 0;
}

int		parse_directive(const char *str, int *i, va_list args, int *na)
{
	va_list		cpy;
	t_directive	d;

	va_copy(cpy, args);
	init_directive(&d, i, na);
	if (parse_next_argument(&d, str, i))
	{
		d.len = *i - d.pos + 1;
		if (d.valid)
		{
			if (d.fl_arg == 2)
				d.fl = (*na)++;
			if (d.p_arg == 2)
				d.p = (*na)++;
			d.na = (*na)++;
		}
		set_base(&d);
		set_args(&d, cpy);
		va_end(cpy);
		return (write_directive(&d, cpy));
	}
	va_end(cpy);
	return (-1);
}

void	set_args(t_directive *d, va_list cpy)
{
	va_list cpy2;
	char	flags[2];
	int		n;

	flags[0] = (d->fl_arg > 1) ? d->fl : 0;
	flags[1] = (d->p_arg > 1) ? d->p : 0;
	if (flags[0] || flags[1])
	{
		va_copy(cpy2, cpy);
		while (flags[0] > 0 || flags[1] > 0)
		{
			n = va_arg(cpy2, int);
			if (!--flags[0])
			{
				d->fl = (n < 0) ? -n : n;
				d->la = (n < 0) ? 1 : d->la;
			}
			if (!--flags[1])
			{
				d->p = (n < 0) ? 1 : n;
				d->p_arg = (n < 0) ? 0 : d->p_arg;
			}
		}
		va_end(cpy2);
	}
}

void	set_base(t_directive *d)
{
	const static t_base hex = {"0123456789abcdef", 16};
	const static t_base helx = {"0123456789ABCDEF", 16};
	const static t_base oct = {"01234567", 8};
	const static t_base bin = {"01", 2};

	if (d->cs == 'x' || d->cs == 'p')
		d->base = &hex;
	else if (d->cs == 'X')
		d->base = &helx;
	else if (d->cs == 'o' || d->cs == 'O')
		d->base = &oct;
	else if (d->cs == 'b')
		d->base = &bin;
}
