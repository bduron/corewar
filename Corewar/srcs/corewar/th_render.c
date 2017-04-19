/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:42:03 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/19 07:45:29 by wolrajhti        ###   ########.fr       */
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
		wattroff(v->win_arena, COLOR_PAIR(v->vm->a.owner[i] + 2));
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
			mvwprintw(v->win_arena, i / 64, (i % 64 * 3), "%.2x", v->vm->a.arena[i]);
			v->arena[i] = v->vm->a.arena[i];
			v->arena_flag[i] = 1;
			wattroff(v->win_arena, COLOR_PAIR(v->vm->a.owner[i] + 2));
			wattroff(v->win_arena, A_BOLD);
		}
		else if (v->arena_flag[i])
		{
			wattron(v->win_arena, COLOR_PAIR(v->vm->a.owner[i] + 2));
			mvwprintw(v->win_arena, i / 64, (i % 64 * 3), "%.2x", v->vm->a.arena[i]);
			wattroff(v->win_arena, COLOR_PAIR(v->vm->a.owner[i] + 2));
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
			mvwprintw(v->win_processes, i - v->process_offset, 0, "carry: %#.2x, pc: %#.2x, "
				"live count: %#.2x, op cast: %#.2x, reg: [", CARRY, PC, LIVE, OP_CAST);
			for (int j = 0; j < REG_NUMBER; j++)
				wprintw(v->win_processes, "%.2x ", REG[j]);
			wprintw(v->win_processes, "]");
			wattroff(v->win_processes, COLOR_PAIR(v->vm->a.owner[PC] + 2));
		}
		wattron(v->win_arena, COLOR_PAIR(v->vm->a.owner[PC] + 2 + 6 ));
		mvwprintw(v->win_arena, PC / 64, (PC % 64 * 3), "%.2x", v->vm->a.arena[PC]);
		wattroff(v->win_arena, COLOR_PAIR(v->vm->a.owner[PC] + 2 + 6 ));
		process = process->next;
	}
	wrefresh(v->win_processes);
	wrefresh(v->win_arena);
	process = v->vm->process_lst;
	while (process)
	{
		wattron(v->win_arena, COLOR_PAIR(v->vm->a.owner[PC] + 2));
		mvwprintw(v->win_arena, PC / 64, (PC % 64 * 3), "%.2x", v->vm->a.arena[PC]);
		wattroff(v->win_arena, COLOR_PAIR(v->vm->a.owner[PC] + 2));
		process = process->next;
	}
}

void	*th_render_routine(void *p_data)
{
	t_viewer	*v;

	v = (t_viewer *)p_data;
	pthread_mutex_lock(&v->mutex);
	init_arena(v);
	maj_process(v);
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

			/* mise à jour des infos générales */
			mvwprintw(v->win_infos, 0, 70, "%7d", v->vm->ncycle);
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
