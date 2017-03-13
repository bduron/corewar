/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:09:56 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 15:36:06 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_memory.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 && *s2 && *(t_byte*)s1 == *(t_byte*)s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n)
		return (*(t_byte*)s1 - *(t_byte*)s2);
	return (0);
}
