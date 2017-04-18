/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:52:23 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/18 18:49:14 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int						lexical_error(t_token token, int ft_errnum)
{
	ft_putstr("Lexical error at [");
	ft_putnbr(token.line);
	ft_putstr(":");
	ft_putnbr(token.col);
	ft_putendl("]");
	return (ft_errnum);
}

static unsigned int		reverse_byte_32(unsigned int num)
{
	unsigned int		reverse;

	reverse = 0x000000FF & num;
	reverse = (reverse << 8) + ((0x0000FF00 & num) >> 8);
	reverse = (reverse << 8) + ((0x00FF0000 & num) >> 16);
	reverse = (reverse << 8) + ((0xFF000000 & num) >> 24);
	return (reverse);
}

static unsigned short	reverse_byte_16(unsigned int num)
{
	unsigned short		reverse;

	reverse = 0x00FF & num;
	reverse = (reverse << 8) + ((0xFF00 & num) >> 8);
	return (reverse);
}

ssize_t					fixed_write(int fildes, const void *buf, size_t nbyte)
{
	unsigned int		fixed;

	if (nbyte == 4)
		fixed = reverse_byte_32(*(unsigned int*)buf);
	else if (nbyte == 2)
		fixed = reverse_byte_16(*(unsigned int*)buf);
	else
		fixed = *(unsigned int*)buf;
	return (write(fildes, &fixed, nbyte));
}

t_char					scanner(int fd)
{
	static int			col = 0;
	static int			line = 1;
	char				c;

	col++;
	if (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
		{
			col = 0;
			line++;
		}
		return ((t_char){c, col, line});
	}
	else
		return ((t_char){-1, col, line});
}
