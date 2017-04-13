/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolrajht <wolrajht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 13:16:25 by wolrajht          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:55 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		write_loop(const char c, int n)
{
	int printed;

	printed = 0;
	while (n > 0 && n--)
	{
		printed++;
		write(1, &c, 1);
	}
	return (printed);
}

int		ft_wctomb(char *s, wchar_t wc)
{
	static int	offsets[6] = {127, 2047, 65535, 2097151, 67108863, 2147483647};
	int			i;
	int			j;
	int			k;

	i = -1;
	while (++i < 6)
		s[0] = 0;
	i = -1;
	while (++i < 6)
		if (wc <= offsets[i])
		{
			j = (i) ? -1 : 0;
			while (++j < i + 1)
			{
				s[0] += 1 << (7 - j);
				s[j] = 1 << 7;
			}
			s[0] += wc >> (i * 6);
			while (--j && (k = (i + 1 - j) * 6))
				s[j] += (wc - (wc >> k << k)) >> (k - 6);
			break ;
		}
	return (i + 1);
}

size_t	ft_itoa_base(char **dest, unsigned long long src, const t_base *b)
{
	size_t				len;
	size_t				i;
	unsigned long long	cpy;

	len = (src) ? 0 : 1;
	cpy = src;
	while (cpy && ++len)
		cpy /= b->len;
	if (!(*dest = (char *)malloc(len + 1)))
		return (0);
	i = len;
	(*dest)[i] = '\0';
	while (i--)
	{
		(*dest)[i] = b->charset[src % b->len];
		src /= b->len;
	}
	return (len);
}
