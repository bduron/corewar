/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 10:07:11 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:49 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		parse_length_modifier(t_directive *d, const char *str, int *i)
{
	if (str[*i] == 'h' && ++(*i))
	{
		d->lm = 'h';
		if (str[*i] == 'h' && ++(*i))
			d->lm = 'H';
	}
	else if (str[*i] == 'l' && ++(*i))
	{
		d->lm = 'l';
		if (str[*i] == 'l' && ++(*i))
			d->lm = 'L';
	}
	else if (str[*i] == 'j' && ++(*i))
		d->lm = 'j';
	else if (str[*i] == 'z' && ++(*i))
		d->lm = 'z';
	else
		return (parse_conversion_specifier(d, str, i));
	return (parse_conversion_specifier(d, str, i));
}

int		parse_conversion_specifier(t_directive *d, const char *str, int *i)
{
	if (str[*i] == 'd' || str[*i] == 'D' || str[*i] == 'b'
	|| str[*i] == 'c' || str[*i] == 'C' || str[*i] == 'p'
	|| str[*i] == 's' || str[*i] == 'S' || str[*i] == 'i'
	|| str[*i] == 'x' || str[*i] == 'X' || str[*i] == 'o'
	|| str[*i] == 'u' || str[*i] == 'U' || str[*i] == 'O')
	{
		d->valid = 1;
		if (str[*i] == 'D' || str[*i] == 'O'
		|| str[*i] == 'U' || str[*i] == 'C'
		|| str[*i] == 'S' || str[*i] == 'p')
			d->lm = 'l';
	}
	d->cs = str[*i];
	if (d->cs)
		++(*i);
	return (1);
}
