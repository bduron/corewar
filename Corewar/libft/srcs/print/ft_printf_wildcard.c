/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 17:55:33 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 17:59:40 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include "ft_utils.h"
#include "ft_string.h"
#include "ft_ctype.h"

static int	ft_get_number(const char **str, int *dest)
{
	const char	*start;
	char		*tmp;

	start = *str;
	while (ft_isdigit(**str))
		(*str)++;
	tmp = ft_strsub(start, 0, (size_t)(*str - start));
	*dest = ft_atoi(tmp);
	ft_strdel(&tmp);
	return (*dest);
}

static int	ft_get_wildcard(va_list ap, const char **str, int *dest)
{
	int		res;

	if (**str == '*')
	{
		*dest = va_arg(ap, int);
		(*str)++;
	}
	else if (!ft_get_number(str, dest))
		return (0);
	if (ft_get_wildcard(ap, str, &res))
		*dest = res;
	return (1);
}

void		ft_get_width(va_list ap, const char **str, t_format *format)
{
	ft_get_wildcard(ap, str, &format->width);
	if (format->width < 0)
	{
		format->width = -(format->width);
		format->flags.minus = 1;
	}
	if (**str == '.')
	{
		(*str)++;
		ft_get_wildcard(ap, str, &format->precision);
		if (format->precision < 0)
			format->precision = -1;
	}
	else
		format->precision = -1;
	while (**str == '.' || ft_isdigit(**str))
		(*str)++;
}
