/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:45:17 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 12:45:24 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_printf_itoa(uintmax_t n)
{
	char			*s;
	int				i;
	long long		nb;
	long long		sign;

	sign = n;
	nb = n;
	i = 2 + ((intmax_t)n < 0);
	while (n /= 10)
		i++;
	if (!(s = (char *)malloc(sizeof(char) * i--)))
		return (NULL);
	s[i--] = '\0';
	s[i--] = nb % 10 + '0';
	while (nb /= 10)
		s[i--] = nb % 10 + '0';
	if (sign < 0)
		*s = '-';
	return (s);
}
