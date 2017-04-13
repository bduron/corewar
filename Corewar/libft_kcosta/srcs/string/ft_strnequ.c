/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:38:57 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 18:55:20 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int		ft_strnequ(const char *s1, const char *s2, size_t n)
{
	if (!s1 || !s2)
		return (1);
	if (ft_strncmp(s1, s2, n))
		return (0);
	return (1);
}
