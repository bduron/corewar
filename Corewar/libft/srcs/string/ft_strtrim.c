/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 18:21:56 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 15:26:40 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strtrim(char const *s)
{
	char const	*strend;

	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	if (!*s)
		return (ft_strnew(0));
	strend = s + ft_strlen(s) - 1;
	while (*strend == ' ' || *strend == '\t' || *strend == '\n')
		strend--;
	return (ft_strsub(s, 0, strend - s + 1));
}
