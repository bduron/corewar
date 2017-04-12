/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:31:48 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:09 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstat(t_list *alst, unsigned int n)
{
	if (!alst)
		return (0);
	while (n-- > 0 && alst->next)
		alst = alst->next;
	return ((n == (unsigned int)(-1)) ? alst : 0);
}
