/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:42:03 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/14 12:21:21 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

static void	wprintw_process(t_viewer *v, int i, t_list *process)
{
	wprintw(v->win_champions[i], "carry: %d", CARRY);
	wprintw(v->win_champions[i], ", pc: %d", PC);
	wprintw(v->win_champions[i], ", live count: %d", LIVE);
	wprintw(v->win_champions[i], ", op cast: %d", OP_CAST);
	wprintw(v->win_champions[i], ", reg: [");
	for (int j = 0; j < REG_NUMBER; j++)
		wprintw(v->win_champions[i], "% 3d", REG[j]);
	wprintw(v->win_champions[i], "]");
}

void	*th_render_routine(void *p_data)
{
	t_viewer	*v;
	int			i;
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
				wattron(v->win_arena, COLOR_PAIR(v->vm->a.owner[i] + 2));
				wprintw(v->win_arena, "%.2x ", v->vm->a.arena[i]);
			}
			wrefresh(v->win_arena);

			/* mise à jour des joueurs */
			// i = -1;
			// while (++i < 4)
			// {
			// 	werase(v->win_champions[i]);
			// 	mvwprintw(v->win_champions[i], 0, 0, v->events[i]);
			// 	wrefresh(v->win_champions[i]);
			// }

			i = -1;
			while (++i < v->vm->nplayer)
			{
				werase(v->win_champions[i]);
				wmove(v->win_champions[i], 0, 0);
				tmp = v->vm->process_lst;
				// j = -1;
				while (tmp)
				{
					// ++j;
					if (((t_process *)tmp->content)->reg[0] == v->vm->p[i].nplayer)
						wprintw_process(v, i, tmp);
					tmp = tmp->next;
				}
				wrefresh(v->win_champions[i]);
			}

			/* mise à jour des infos générales */
			wmove(v->win_infos, 0, 100);
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
