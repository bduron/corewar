/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:52:23 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/18 17:01:10 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

char					scanner(int fd)
{
	char	c;

	if (read(fd, &c, 1) > 0)
		return (c);
	else
		return (-1);
}
