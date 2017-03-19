/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 10:20:13 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:21:54 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		count_digits(int nb)
{
	int len;

	len = (nb == 0) ? 1 : 0;
	if (nb < 0)
	{
		len++;
		nb = -nb;
	}
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

int		max(int x, int y, int z)
{
	int max;

	max = (x >= y) ? x : y;
	max = (max >= z) ? max : z;
	return (max);
}

int		is_x(t_flags *f)
{
	return (f->id == 'x' || f->id == 'X' ? 1 : 0);
}

int		pad(int len, char c)
{
	if (len < 0)
		return (0);
	while (len)
	{
		ft_putchar(c);
		len--;
	}
	return (0);
}

int		isnt_id(t_flags *f)
{
	char	*ids;
	int		i;

	ids = "DdiOoUuxXcCsSbp";
	i = 0;
	while (ids[i])
		if (f->id == ids[i++])
			return (0);
	return (1);
}
