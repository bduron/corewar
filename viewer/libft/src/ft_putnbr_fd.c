/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:12:56 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:46:05 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	rec(unsigned int t, int fd)
{
	if (t > 9)
		rec(t / 10, fd);
	ft_putchar_fd('0' + (t - (t / 10 * 10)), fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	unsigned int m;

	m = (n < 0) ? -n : n;
	if (n < 0)
		ft_putchar_fd('-', fd);
	rec(m, fd);
}
