/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_digits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:25:46 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:21:54 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*itobin(unsigned long long n, char *p)
{
	*--p = (n & 0x1) ? '1' : '0';
	while (n >>= 1)
		*--p = (n & 0x1) ? '1' : '0';
	return (p);
}

char	*itob(t_flags *f, unsigned long long n)
{
	char *p;

	p = &f->str[255];
	if (f->flags['b'])
		return (itobin(n, p));
	if (f->id == 'o')
	{
		*--p = (n & 0x7) + '0';
		while (n >>= 3)
			*--p = (n & 0x7) + '0';
		if ((f->flags['#'] && *p != '0') && (f->precision < (int)ft_strlen(p)))
			*--p = '0';
		return (p);
	}
	if (is_x(f))
	{
		*--p = (f->id == 'x') ? HEX_L[n & 0xf] : HEX_U[n & 0xf];
		while (n >>= 4)
			*--p = (f->id == 'x') ? HEX_L[n & 0xf] : HEX_U[n & 0xf];
		return (p);
	}
	*--p = n % 10 + '0';
	while (n /= 10)
		*--p = n % 10 + '0';
	return (p);
}

void	conv_u(t_flags *f)
{
	char			*s;
	unsigned long	nb;

	nb = get_arg_u(f);
	if (f->flags['.'])
		f->flags['0'] = 0;
	s = itob(f, nb);
	s = (nb == 0 && f->precision == 0 && f->id != 'o') ? "" : s;
	put_d(f, s, ft_strlen(s));
}

void	conv_d(t_flags *f)
{
	char			*s;
	long long		nb;
	unsigned long	m;

	nb = ((f->id == 'd' || f->id == 'i') && !f->flags['u']) ?
		get_arg(f) : get_arg_u(f);
	if (nb < 0 && f->id != 'o' && !is_x(f))
		f->sign = '-';
	else if (f->flags['+'] && f->id != 'o' && !is_x(f))
		f->sign = '+';
	else if (f->flags[' '])
		f->sign = ' ';
	f->s_bool = (f->sign) ? 1 : 0;
	if (f->flags['.'])
		f->flags['0'] = 0;
	m = (nb > 0) ? nb : -nb;
	s = (is_x(f) || f->id == 'o') ? itob(f, nb) : itob(f, m);
	s = (nb == 0 && f->precision == 0 && f->id != 'o') ? "" : s;
	s = (nb == 0 && f->precision == 0 && f->id == 'o' && !f->flags['#'])
		? "" : s;
	f->h_bool = (f->flags['#'] && *s != '0' && *s && is_x(f)) ? 2 : 0;
	f->h_bool += (!f->h_bool && f->flags['p']) ? 2 : 0;
	put_d(f, s, ft_strlen(s) + f->s_bool + f->h_bool);
}

void	put_d(t_flags *f, char *s, int len)
{
	int n;

	n = (f->precision > len - f->s_bool - f->h_bool) ?
		f->precision : len - f->s_bool - f->h_bool;
	(f->sign && f->flags['0']) ? ft_putchar(f->sign) : 0;
	if (f->width > n && !f->flags['-'] && !f->flags['0'])
		pad(f->width - n - f->s_bool - f->h_bool, ' ');
	if (f->flags['#'] && is_x(f) && ((*s != '0' && *s) || f->flags['p']))
	{
		ft_putchar('0');
		(f->id == 'x' && !f->flags['b']) ? ft_putchar('x') : 0;
		(f->id == 'X' && !f->flags['b']) ? ft_putchar('X') : 0;
		(f->id == 'x' && f->flags['b']) ? ft_putchar('b') : 0;
	}
	if (f->width > n && !f->flags['-'] && f->flags['0'])
		pad(f->width - n - f->s_bool - f->h_bool, '0');
	(f->sign && !f->flags['0']) ? ft_putchar(f->sign) : 0;
	if (f->precision > len - f->s_bool - f->h_bool)
		pad(f->precision - len + f->s_bool + f->h_bool, '0');
	ft_putstr(s);
	(f->width > n && f->flags['-']) ?
		pad(f->width - n - f->s_bool - f->h_bool, ' ') : 0;
	f->plen += max(f->width, f->precision + f->s_bool + f->h_bool, len);
}
