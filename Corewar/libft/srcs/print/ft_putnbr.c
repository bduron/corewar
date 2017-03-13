/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 11:54:08 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 17:10:01 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

static int	ft_dcount(int n)
{
	int		digits;

	digits = 0;
	if (!n)
		return (1);
	while (n != 0)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

void		ft_putnbr(int n)
{
	long	nbr;
	int		digits;
	int		power;

	digits = ft_dcount(n);
	power = 1;
	while (--digits > 0)
		power *= 10;
	nbr = (long)n;
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr = -nbr;
	}
	while (power > 0)
	{
		ft_putchar(nbr / power + '0');
		nbr %= power;
		power /= 10;
	}
}
