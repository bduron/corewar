/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:42:03 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/15 17:41:00 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

void	wprintw_process(t_viewer *v, int i, t_list *process)
{
	if (v->process_offset <= i && i - v->process_offset < getmaxy(v->win_processes))
	{
		wattron(v->win_processes, COLOR_PAIR(1));
		wmove(v->win_processes, i - v->process_offset, 0);
		wprintw(v->win_processes, "carry: %#.2x", CARRY);
		wprintw(v->win_processes, ", pc: %#.2x", PC);
		wprintw(v->win_processes, ", live count: %#.2x", LIVE);
		wprintw(v->win_processes, ", op cast: %#.2x", OP_CAST);
		wprintw(v->win_processes, ", reg: [");
		for (int j = 0; j < REG_NUMBER; j++)
			wprintw(v->win_processes, "%.2x ", REG[j]);
		wprintw(v->win_processes, "]");
		wattroff(v->win_processes, COLOR_PAIR(1));
	}
}

void	*th_render_routine(void *p_data)
{
	t_viewer	*v;
	int			i;
	char		flag;
	// int			j;
	t_list		*tmp;

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

			/* mise à jour de l'arène */
			werase(v->win_arena);
			wmove(v->win_arena, 0, 0);
			i = -1;
			while (++i < MEM_SIZE)
			{
				flag = 0;
				tmp = v->vm->process_lst;
				while (tmp)
				{
					if (((t_process *)tmp->content)->pc == i)
					{
						wattron(v->win_arena, COLOR_PAIR(6));
						flag = 1;
						break ;
					}
					tmp = tmp->next;
				}
				if (!flag)
				{
					wattron(v->win_arena, COLOR_PAIR(v->vm->a.owner[i] + 2));
					flag = 2;
				}
				wprintw(v->win_arena, "%.2x ", v->vm->a.arena[i]);
				if (flag == 1)
					wattroff(v->win_arena, COLOR_PAIR(6));
				else
					wattroff(v->win_arena, COLOR_PAIR(v->vm->a.owner[i] + 2));

			}
			wrefresh(v->win_arena);

			/* mise à jour des joueurs */
			werase(v->win_processes);
			i = -1;
			tmp = v->vm->process_lst;
			while (tmp)
			{
				wprintw_process(v, ++i, tmp);
				tmp = tmp->next;
			}
			wrefresh(v->win_processes);

			/* mise à jour des infos générales */
			wmove(v->win_infos, 0, 70);
			wprintw(v->win_infos, "%7d", v->vm->ncycle);
			wrefresh(v->win_infos);

			v->event_flags ^= (FLAG_EVENT_CORE | FLAG_EVENT_TIMER);
			pthread_cond_broadcast(&v->cond);
		}
		else
			pthread_cond_wait(&v->cond, &v->mutex);
	}
	pthread_mutex_unlock(&v->mutex);
	pthread_exit(0);
}
