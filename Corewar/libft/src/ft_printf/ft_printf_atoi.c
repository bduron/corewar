/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_atoi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:44:00 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 12:44:05 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf_atoi(const char *str)
{
	int is_negative;
	int n;

	n = 0;
	is_negative = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v' ||
			*str == '\r' || *str == '\f')
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		is_negative = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + (*str - '0');
		str++;
	}
	return (is_negative ? -n : n);
}
