/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_strings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:27:01 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:58:03 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_putwchar(wchar_t c)
{
	size_t	utf;
	size_t	mask;
	int		shift;
	int		nboctet;

	utf = 0;
	shift = 8;
	nboctet = (c > 0xffff) ? 2 : 1;
	utf = (c <= 0x1fffff) ? 0b11110000100000001000000010000000 : utf;
	utf = (c <= 0xffff) ? 0b111000001000000010000000 : utf;
	utf = (c <= 0x7ff) ? 0b1100000010000000 : utf;
	utf = (c <= 0x7f) ? 0b00000000 : utf;
	utf = (utf) ? (c & 0x3f) | utf : (c & 0x7f) | utf;
	while (c > 0x7f && (c >>= 6))
	{
		mask = c & 0x3f;
		mask <<= shift;
		utf = mask | utf;
		shift += shift;
		nboctet++;
	}
	shift = 0;
	while (shift < nboctet)
		ft_putchar((utf << (shift++ * 8)) >> ((nboctet - 1) * 8));
	return (nboctet);
}

void	put_s(t_flags *f)
{
	char	*s;
	size_t	len;
	int		n;

	if (!(s = va_arg(f->ap, char *)))
		s = "(null)";
	len = ft_strlen(s);
	if (f->precision >= 0 && (size_t)f->precision < len)
		len = f->precision;
	n = len;
	if (!f->flags['-'])
		(f->flags['0']) ? pad(f->width - len, '0') : pad(f->width - len, ' ');
	while (n--)
		ft_putchar(*s++);
	if (f->flags['-'])
		pad(f->width - len, ' ');
	if (len != 0)
		f->plen += max(f->width, 0, len);
	else
		f->plen += f->width;
}

size_t	ft_strwlen(wchar_t *s)
{
	size_t len;

	len = 0;
	while (*s != L'\0')
	{
		if (*s <= 0x7F)
			len += 1;
		else if (*s <= 0x7FF)
			len += 2;
		else if (*s <= 0xFFFF)
			len += 3;
		else if (*s <= 0x10FFFF)
			len += 4;
		s++;
	}
	return (len);
}

void	put_s_maj(t_flags *f)
{
	wchar_t	*s;
	size_t	len;
	long	n;
	long	nb_octet;

	if (!(s = va_arg(f->ap, wchar_t *)))
		s = L"(null)";
	len = ft_strwlen(s);
	if (f->precision >= 0 && (size_t)f->precision < len)
		len = f->precision;
	n = (long)len;
	if (!f->flags['-'])
		(f->flags['0']) ? pad(f->width - len, '0')
			: pad(f->width - len + rem(len, s), ' ');
	while (n > 0 && *s && (long)ft_wlen(*s) <= n)
	{
		nb_octet = ft_putwchar(*s++);
		n -= nb_octet;
	}
	if (f->flags['-'])
		pad(f->width - len, ' ');
	f->plen += (len != 0) ? max(f->width, 0, len - (size_t)n) : f->width;
}

void	put_c(t_flags *f)
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
	else
		ft_putchar(c);
	f->flags['-'] ? pad(f->width - 1, ' ') : 0;
	f->plen += n;
	f->plen -= (c > 127 && f->mod['l']) ? 1 : 0;
}
