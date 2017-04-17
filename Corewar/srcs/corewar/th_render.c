/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:42:03 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/17 19:36:44 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

void	init_arena(t_viewer *v)
{
	int	i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		wattron(v->win_arena, COLOR_PAIR(v->vm->a.owner[i] + 2));
		mvwprintw(v->win_arena, i / 64, (i % 64 * 3), "%.2x ", v->vm->a.arena[i]);
		// mvwprintw(v->win_arena, i / 64, (i % 64 * 3), "%.2x ", i);
		v->arena[i] = v->vm->a.arena[i];
	}
	wrefresh(v->win_arena);
}

void	maj_arena(t_viewer *v)
{
	int	i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (v->arena[i] != v->vm->a.arena[i])
		{
			wattron(v->win_arena, A_BOLD);
			wattron(v->win_arena, COLOR_PAIR(v->vm->a.owner[i] + 2));
			mvwprintw(v->win_arena, i / 64, (i % 64 * 3), "%.2x ", v->vm->a.arena[i]);
			v->arena[i] = v->vm->a.arena[i];
			v->arena_flag[i] = 1;
			wattroff(v->win_arena, A_BOLD);
		}
		else if (v->arena_flag[i]) // réécrire à la fin du tour en police normale pour se passer de arena_flag...
		{
			wattron(v->win_arena, COLOR_PAIR(v->vm->a.owner[i] + 2));
			mvwprintw(v->win_arena, i / 64, (i % 64 * 3), "%.2x ", v->vm->a.arena[i]);
			v->arena_flag[i] = 0;
		}
	}
	wrefresh(v->win_arena);
}

void	maj_process(t_viewer *v)
{
	int		i;
	t_list	*process;

	werase(v->win_processes);
	i = -1;
	process = v->vm->process_lst;
	while (process)
	{
		++i;
		if (v->process_offset <= i && i - v->process_offset < getmaxy(v->win_processes))
		{
			wattron(v->win_processes, COLOR_PAIR(v->vm->a.owner[PC] + 2));
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
		wattron(v->win_arena, COLOR_PAIR(v->vm->a.owner[PC] + 2 + 6 ));
		mvwprintw(v->win_arena, PC / 64, (PC % 64 * 3), "%.2x", v->vm->a.arena[PC]);
		process = process->next;
	}
	wrefresh(v->win_processes);
}

void	*th_render_routine(void *p_data)
{
	t_viewer	*v;

	v = (t_viewer *)p_data;
	pthread_mutex_lock(&v->mutex);
	init_arena(v);
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
			maj_arena(v);

			/* mise à jour des joueurs */
			maj_process(v);

			// TODO faire une boucle pour supprimer les process et les octets en gras

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
