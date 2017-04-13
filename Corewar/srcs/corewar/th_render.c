/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:42:03 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/13 18:24:28 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

void	*th_render_routine(void *p_data)
{
	t_viewer	*v;
	int			i;
	// int			y;
	// int			x;
	// int			max_y;
	// int			max_x;

	v = (t_viewer *)p_data;
	pthread_mutex_lock(&v->mutex);
	while(1)
	{
		// printf("RENDER");
		if (v->event_flags & FLAG_EVENT_QUIT)
		{
			pthread_mutex_unlock(&v->mutex);
			pthread_exit(0);
		}
		if ((v->event_flags & FLAG_EVENT_CORE)
			&& (v->event_flags & FLAG_EVENT_TIMER)
			&& !(v->event_flags & FLAG_EVENT_PAUSE))
		{
			werase(v->win_arena);
			wmove(v->win_arena, 0, 0);
			// getyx(v->win_arena, y, x);
			// getmaxyx(v->win_arena, max_y, max_x);
			// while (y < max_y + 1)
			// {
			// 	while (x < max_x)
			// 	{
			//
			// 		++x;
			// 	}
			// 	++y;
			// }
			i = -1;
			while (++i < MEM_SIZE)
			{
				wattron(v->win_arena, COLOR_PAIR(v->vm->a.owner[i] + 2));
				wprintw(v->win_arena, "%.2x ", v->vm->a.arena[i]);
			}
			wrefresh(v->win_arena);
			i = -1;
			while (++i < 4)
			{
				werase(v->win_champions[i]);
				mvwprintw(v->win_champions[i], 0, 0, v->events[i]);
				wrefresh(v->win_champions[i]);
			}
			v->event_flags ^= (FLAG_EVENT_CORE | FLAG_EVENT_TIMER);
			pthread_cond_broadcast(&v->cond);
		}
		else
			pthread_cond_wait(&v->cond, &v->mutex);
	}
	pthread_mutex_unlock(&v->mutex);
	pthread_exit(0);
}
