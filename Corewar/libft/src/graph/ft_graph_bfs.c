/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_bfs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <bduron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 17:58:44 by bduron            #+#    #+#             */
/*   Updated: 2017/04/13 16:02:18 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	initialize_bfs(t_graph *g)
{
	int i;

	i = 0;
	while (i < g->nvertices)
	{
		g->bfs_processed[i] = FT_FALSE;
		g->bfs_discovered[i] = FT_FALSE;
		g->bfs_parent[i] = -1;
		i++;
	}
}

void	process_vertex_late(int v)
{
	(void)v;
	return ;
}

void	process_vertex_early(int v)
{
	(void)v;
	return ;
}

void	process_edge(int v, int y)
{
	(void)v;
	(void)y;
	return ;
}

void	bfs_norme(t_graph *g, int start, t_bfs *b)
{
	b->queue = ft_lstnew(&start, sizeof(start));
	g->bfs_discovered[start] = FT_TRUE;
	while (b->queue != NULL)
	{
		b->pop = ft_lstpop(&(b->queue));
		b->v = *(b->pop);
		process_vertex_early(b->v);
		g->bfs_processed[b->v] = FT_TRUE;
		b->p = g->edges[b->v];
		while (b->p != NULL)
		{
			b->y = b->p->y;
			if (g->bfs_processed[b->y] == FT_FALSE)
				process_edge(b->v, b->y);
			if (g->bfs_discovered[b->y] == FT_FALSE)
			{
				ft_lstappend(&(b->queue), ft_lstnew(&(b->y), sizeof(int)));
				g->bfs_discovered[b->y] = FT_TRUE;
				g->bfs_parent[b->y] = b->v;
			}
			b->p = b->p->next;
		}
		process_vertex_late(b->v);
		free(b->pop);
	}
}

/*
**
** real BFS, 31 lines ><
**
**void	bfs(t_graph *g, int start)
**{
**	t_list		*queue;
**	int			v;
**	int			*pop;
**	int			y;
**	t_edgenode	*p;
**
**	queue = ft_lstnew(&start, sizeof(start));
**	g->bfs_discovered[start] = FT_TRUE;
**	while (queue != NULL)
**	{
**		pop = ft_lstpop(&queue);
**		v = *pop;
**		process_vertex_early(v);
**		g->bfs_processed[v] = FT_TRUE;
**		p = g->edges[v];
**		while (p != NULL)
**		{
**			y = p->y;
**			if (g->bfs_processed[y] == FT_FALSE)
**				process_edge(v, y);
**			if (g->bfs_discovered[y] == FT_FALSE)
**			{
**				ft_lstappend(&queue, ft_lstnew(&y, sizeof(int)));
**				g->bfs_discovered[y] = FT_TRUE;
**				g->bfs_parent[y] = v;
**			}
**			p = p->next;
**		}
**		process_vertex_late(v);
**		free(pop);
**	}
**}
*/