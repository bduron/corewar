/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:53:02 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 15:25:56 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	if (!(join = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	return (ft_strcat(ft_strcat(join, s1), s2));
}
