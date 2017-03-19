/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:18:13 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 12:46:20 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_flags(char *s, t_flags *f)
{
	s++;
	while (is_flag(*s))
		f->flags[(int)*s++]++;
	s = get_wildcards(f, s);
	while (is_mod(*s))
	{
		*s == *(s + 1) ? f->mod[(int)ft_toupper(*s++)]++ : f->mod[(int)*s++]++;
		*s == *(s - 1) ? s++ : 0;
	}
	if (is_id(*s))
		f->id = *s;
	else
		--s;
	(f->id == 0) ? f->plen-- : 0;
	return (s);
}

int		is_flag(char c)
{
	if (c == '0')
		return (1);
	if (c == ' ')
		return (1);
	if (c == '-')
		return (1);
	if (c == '#')
		return (1);
	if (c == '+')
		return (1);
	if (c == '\'')
		return (1);
	return (0);
}

int		is_mod(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	return (0);
}

int		is_id(char id)
{
	if (id == 's' || id == 'S')
		return (1);
	if (id == 'd' || id == 'D')
		return (1);
	if (id == 'o' || id == 'O')
		return (1);
	if (id == 'u' || id == 'U')
		return (1);
	if (id == 'x' || id == 'X')
		return (1);
	if (id == 'c' || id == 'C')
		return (1);
	if (id == 'p' || id == 'i')
		return (1);
	if (id == '%' || ft_isalpha(id))
		return (1);
	return (0);
}

void	reset_flags(t_flags *f)
{
	ft_memset(f->flags, 0, sizeof(int) * 256);
	ft_memset(f->mod, 0, sizeof(int) * 256);
	ft_memset(f->str, 0, 256);
	f->width = 0;
	f->precision = -1;
	f->sign = 0;
	f->s_bool = 0;
	f->h_bool = 0;
}
