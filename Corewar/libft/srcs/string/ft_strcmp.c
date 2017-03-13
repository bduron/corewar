/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:03:39 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/04 15:31:09 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_memory.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *(t_byte*)s1 == *(t_byte*)s2)
	{
		s1++;
		s2++;
	}
	return (*(t_byte*)s1 - *(t_byte*)s2);
}
