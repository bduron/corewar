/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 10:07:11 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:47 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		parse_int(int *dest, const char *str, int *i)
{
	*dest = 0;
	if (str[*i] < '0' || str[*i] > '9')
		return (0);
	while (str[*i] >= '0' && str[*i] <= '9')
		*dest = *dest * 10 + str[(*i)++] - '0';
	return (1);
}

int		parse_next_argument(t_directive *d, const char *str, int *i)
{
	int	tmp;

	if (str[*i] == '0')
		return (parse_flag(d, str, i));
	if (parse_int(&tmp, str, i) && str[*i] == '$' && ++(*i) && (d->na_arg = 3))
		d->na = tmp;
	else if (str[*i] == '$')
		++(*i);
	else if (tmp && ++d->fl_arg)
	{
		d->fl = tmp;
		return (parse_precision(d, str, i));
	}
	return (parse_flag(d, str, i));
}

int		parse_flag(t_directive *d, const char *str, int *i)
{
	if (str[*i] == '#')
		d->af = 1;
	else if (str[*i] == '0')
		d->zp = 1;
	else if (str[*i] == '+')
		d->as = 1;
	else if (str[*i] == '-')
		d->la = 1;
	else if (str[*i] == ' ')
		d->pa = 1;
	else
		return (parse_field_length(d, str, i));
	++(*i);
	return (parse_flag(d, str, i));
}

int		parse_field_length(t_directive *d, const char *str, int *i)
{
	int	tmp;

	if (str[*i] == '*' && ++(*i) && (d->fl_arg = 2))
	{
		if (parse_int(&tmp, str, i) && str[*i] == '$' && ++(*i) && ++d->fl_arg)
			d->fl = tmp;
		else if (str[*i] == '$')
			++(*i);
		return (parse_precision(d, str, i));
	}
	if (parse_int(&d->fl, str, i))
		++d->fl_arg;
	return (parse_precision(d, str, i));
}

int		parse_precision(t_directive *d, const char *str, int *i)
{
	int	tmp;

	if (str[*i] == '.' && ++(*i) && ++d->p_arg)
	{
		if (str[*i] == '*' && ++(*i) && ++d->p_arg)
		{
			if (parse_int(&tmp, str, i)
			&& str[*i] == '$' && ++(*i) && ++d->p_arg)
				d->p = tmp;
			else if (str[*i] == '$')
				++(*i);
			return (parse_length_modifier(d, str, i));
		}
		parse_int(&d->p, str, i);
	}
	return (parse_length_modifier(d, str, i));
}
