/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 07:54:45 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:46:25 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i1;
	size_t	i2;

	if (!s)
		return (NULL);
	i1 = 0;
	while (s[i1] && (s[i1] == ' ' || s[i1] == '\n' || s[i1] == '\t'))
		i1++;
	i2 = ft_strlen(s) - 1;
	if (i1 == i2 + 1)
		return (ft_strnew(0));
	while (i2 > 0 && (s[i2] == ' ' || s[i2] == '\n' || s[i2] == '\t'))
		i2--;
	return (ft_strsub(s, i1, i2 - i1 + 1));
}
