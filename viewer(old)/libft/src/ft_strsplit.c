/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 10:00:37 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:46:23 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] != c && (i == 0 || str[i - 1] == c))
			count++;
	return (count);
}

static int	count_to_next_sep(char const *str, int i, char c)
{
	int j;

	j = 0;
	while (str[i + j] && str[i + j] != c)
		j++;
	return (j);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**ws;

	i = 0;
	j = 0;
	k = 0;
	if (!(s && (ws = (char **)malloc((count_words(s, c) + 1) * sizeof(*ws)))))
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			j = count_to_next_sep(s, i, c);
			if (!(ws[k++] = ft_strsub(s, i, j)))
				return (NULL);
			i += j - 1;
		}
		i++;
	}
	ws[k] = 0;
	return (ws);
}
