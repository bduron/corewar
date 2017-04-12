/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 10:46:05 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:46:16 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*cpy;

	size = 0;
	if (s1)
		while (s1[size])
			size++;
	if (!(cpy = (char *)malloc((size + 1) * sizeof(*cpy))))
		return (0);
	cpy[size] = '\0';
	while (size--)
		cpy[size] = s1[size];
	return (cpy);
}
