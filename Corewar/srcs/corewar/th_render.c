/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:42:03 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/20 17:01:05 by pboutelo         ###   ########.fr       */
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
		v->owner[i] = v->vm->a.owner[i];
	}
	wrefresh(v->win_arena);
}

void	maj_arena(t_viewer *v)
{
	int	i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (v->arena[i] != v->vm->a.arena[i] || v->owner[i] != v->vm->a.owner[i])
		{
			wattron(v->win_arena, A_BOLD);
			wattron(v->win_arena, COLOR_PAIR(v->vm->a.owner[i] + 2));
			mvwprintw(v->win_arena, i / 64, (i % 64 * 3), "%.2x", v->vm->a.arena[i]);
			v->arena[i] = v->vm->a.arena[i];
			v->owner[i] = v->vm->a.owner[i];
			v->arena_flag[i] = v->vm->ncycle;
			wattroff(v->win_arena, COLOR_PAIR(v->vm->a.owner[i] + 2));
			wattroff(v->win_arena, A_BOLD);
		}
		else if (v->arena_flag[i] + 50 < v->vm->ncycle)
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
			if (NPRO == 7)
				wattron(v->win_processes, COLOR_PAIR(4));
			else
				wattron(v->win_processes, COLOR_PAIR(v->vm->a.owner[PC] + 2));
			mvwprintw(v->win_processes, i - v->process_offset, 0, "#%d %dx%d [%c][%c]: ", NPRO, PC / 64, PC % 64, PRINT_LIVE, PRINT_CARRY);
			if (NEXT_OP >= 0 && NEXT_OP < 16)
				wprintw(v->win_processes, "will cast a \"%s\" in %d laps. ", PRINT_NEXT_OP, OP_CAST);
			else
				wprintw(v->win_processes, "looking for instruction. ");
			for (int j = 0; j < REG_NUMBER; j++)
				if(REG[j])
					wprintw(v->win_processes, "%d:%x ", j, REG[j]);
			wattroff(v->win_processes, COLOR_PAIR(v->vm->a.owner[PC] + 2));
		}
		if (NPRO == 7)
			wattron(v->win_arena, COLOR_PAIR(10));
		else
			wattron(v->win_arena, COLOR_PAIR(v->vm->a.owner[PC] + 2 + 6));
		// wattron(v->win_arena, COLOR_PAIR(v->vm->a.owner[PC] + 2 + 6 ));
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
			mvwprintw(v->win_infos, 0, 69, "%-10d", v->vm->ncycle);
			mvwprintw(v->win_infos, 1, 69, "%-10d", v->vm->cycle_to_die);
			// mvwprintw(v->win_infos, 0, 70, "%7d", v->vm->ncycle);
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
