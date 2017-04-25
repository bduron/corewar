/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pourcent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 12:01:17 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 17:58:22 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

int		ft_printf_pourcent(t_format *format)
{
	size_t	size;

	size = 1;
	if (format->flags.minus)
	{
		ft_putchar('%');
		while ((size_t)format->width > size++)
			ft_putchar((format->flags.zero) ? '0' : ' ');
	}
	else
	{
		while ((size_t)format->width > size++)
			ft_putchar((format->flags.zero) ? '0' : ' ');
		ft_putchar('%');
	}
	return (size - 1);
}
