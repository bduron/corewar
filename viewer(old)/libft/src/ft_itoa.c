/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:12:56 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:07 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	unsigned char	count;
	unsigned int	m;
	char			*res;

	count = (n < 0) ? 1 : 0;
	m = (n < 0) ? -n : n;
	while (m > 9)
	{
		m /= 10;
		count++;
	}
	count++;
	if (!(res = (char*)malloc((count + 1) * sizeof(char))))
		return (0);
	res[count] = '\0';
	m = (n < 0) ? -n : n;
	while (m > 9)
	{
		res[--count] = '0' + m % 10;
		m /= 10;
	}
	res[--count] = '0' + m % 10;
	if (n < 0)
		res[0] = '-';
	return (res);
}
