/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_shortestpath.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 18:01:03 by bduron            #+#    #+#             */
/*   Updated: 2017/03/09 18:03:09 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		find_path_rec(int start, int end, int *parents)
{
	if ((start == end) || (end == -1))
		ft_printf("\n%d", start);
	else
	{
		find_path_rec(start, parents[end], parents);
		ft_printf(" %d", end);
	}
}

t_list		*find_path_bfs(int start, int end, int *parents)
{
	int		v;
	t_list	*stack;

	if (!parents || parents[end] == -1)
		return (NULL);
	v = end;
	stack = ft_lstnew(&v, sizeof(int));
	while (parents[v] != start)
	{
		v = parents[v];
		ft_lstpush(&stack, ft_lstnew(&v, sizeof(int)));
	}
	ft_lstpush(&stack, ft_lstnew(&start, sizeof(int)));
	return (stack);
}
