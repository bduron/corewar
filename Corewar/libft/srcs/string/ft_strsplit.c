/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 18:41:48 by kcosta            #+#    #+#             */
/*   Updated: 2016/11/30 15:29:01 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

static int	ft_wcount(const char *s, int c)
{
	int		wcount;

	wcount = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			wcount++;
		while (*s && !(*s == c))
			s++;
	}
	return (wcount);
}

char		**ft_strsplit(const char *s, char c)
{
	char	**split;
	int		words;
	int		index;
	int		length;

	if (!s)
		return (NULL);
	index = 0;
	words = ft_wcount(s, c) + 1;
	if (!(split = (char**)malloc(sizeof(char*) * words)))
		return (NULL);
	while (index < words - 1)
	{
		length = 0;
		while (*s && *s == c)
			s++;
		while (s[length] && !(s[length] == c))
			length++;
		split[index] = ft_strsub(s, 0, length);
		index++;
		s += length;
	}
	split[index] = 0;
	return (split);
}
