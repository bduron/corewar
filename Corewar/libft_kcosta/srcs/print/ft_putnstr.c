/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 17:55:35 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/01 15:00:08 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

ssize_t	ft_putnstr(const char *str, size_t len)
{
	size_t		ret;

	ret = len;
	if (!str)
		return (-1);
	while (len-- && *str)
		ft_putchar(*str++);
	return (ret);
}
