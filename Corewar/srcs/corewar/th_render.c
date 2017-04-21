/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 18:42:03 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/21 19:32:41 by pboutelo         ###   ########.fr       */
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

void	init_register(t_viewer *v)
{
	int i;

	werase(v->win_register);
	i = -1;
	while (++i < REG_NUMBER)
	{
		if (i < REG_NUMBER / 2)
			mvwprintw(v->win_register, 2 * i, 0, "Register[%3d] = %13d", i, 0);
		else
			mvwprintw(v->win_register, 2 * (i - (REG_NUMBER / 2)), 31, "Register[%3d] = %13d", i, 0);
	}
	wrefresh(v->win_register);
}

void	maj_register(t_viewer *v, t_process *process)
{
	int i;

	i = -1;
	while (++i < REG_NUMBER)
	{
		if (i < REG_NUMBER / 2)
			mvwprintw(v->win_register, 2 * i, 16, "%13d", process->reg[i]);
		else
			mvwprintw(v->win_register, 2 * (i - (REG_NUMBER / 2)), 46, "%13d", process->reg[i]);
	}
	wrefresh(v->win_register);
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
			v->arena_flag[i] = v->vm->ncycle + 50;
			wattroff(v->win_arena, COLOR_PAIR(v->vm->a.owner[i] + 2));
			wattroff(v->win_arena, A_BOLD);
		}
		else if (v->arena_flag[i] && v->arena_flag[i] < v->vm->ncycle)
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
	int			i;
	t_list		*process;
	t_process	*selected;

	werase(v->win_processes);
	i = -1;
	process = v->vm->process_lst;
	while (process)
	{
		++i;
		if (v->process_offset <= i && i - v->process_offset < getmaxy(v->win_processes))
		{
			if (i == v->process_selected)
			{
				wattron(v->win_processes, COLOR_PAIR(7));
				selected = (t_process *)process->content;
			}
			else
				wattron(v->win_processes, COLOR_PAIR(v->vm->a.owner[PC] + 2));
			mvwprintw(v->win_processes, i - v->process_offset, 0, "#%-5d %2dx%-2d [%c][%c]: ", NPRO, PC / 64, PC % 64, PRINT_LIVE, PRINT_CARRY);
			if (NEXT_OP >= 0 && NEXT_OP < 16)
				mvwprintw(v->win_processes, i - v->process_offset, 20, "          will cast a \"%5s\" in %4d laps.", PRINT_NEXT_OP, OP_CAST);
			else
				mvwprintw(v->win_processes, i - v->process_offset, 20, "                 is looking for instruction.");
			if (i == v->process_selected)
				wattroff(v->win_processes, COLOR_PAIR(7));
			else
				wattroff(v->win_processes, COLOR_PAIR(v->vm->a.owner[PC] + 2));
		}
		if (i != v->process_selected)
		{
			wattron(v->win_arena, COLOR_PAIR(v->vm->a.owner[PC] + 2 + 6));
			mvwprintw(v->win_arena, PC / 64, (PC % 64 * 3), "%.2x", v->vm->a.arena[PC]);
			wattroff(v->win_arena, COLOR_PAIR(v->vm->a.owner[PC] + 2 + 6 ));
		}
		process = process->next;
	}
	wattron(v->win_arena, COLOR_PAIR(7));
	mvwprintw(v->win_arena, selected->pc / 64, (selected->pc % 64 * 3), "%.2x", v->vm->a.arena[selected->pc]);
	wattroff(v->win_arena, COLOR_PAIR(7));
	maj_register(v, selected);

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

void	update_anim(t_viewer *v, int i, char state)
{
	if (state != v->anim_state[i] && state < v->anim_state[i])
	{
		v->anim_state[i] = state;
		werase(v->win_champions[i]);
		if (state == LIFE_DEAD)
		{
			mvwprintw(v->win_champions[i], 0, 0, "%ls", SKULL_1);
			mvwprintw(v->win_champions[i], 1, 0, "%ls", SKULL_2);
			mvwprintw(v->win_champions[i], 2, 0, "%ls", SKULL_3);
			mvwprintw(v->win_champions[i], 3, 0, "%ls", SKULL_4);
			mvwprintw(v->win_champions[i], 4, 0, "%ls", SKULL_5);
			mvwprintw(v->win_champions[i], 5, 0, "%ls", SKULL_6);
		}
		else if (state == LIFE_LOW)
		{
			mvwprintw(v->win_champions[i], 0, 0, "%ls", LIFE_LOW_1);
			mvwprintw(v->win_champions[i], 1, 0, "%ls", LIFE_LOW_2);
			mvwprintw(v->win_champions[i], 2, 0, "%ls", LIFE_LOW_3);
			mvwprintw(v->win_champions[i], 3, 0, "%ls", LIFE_LOW_4);
			mvwprintw(v->win_champions[i], 4, 0, "%ls", LIFE_LOW_5);
			mvwprintw(v->win_champions[i], 5, 0, "%ls", LIFE_LOW_6);
		}
		else if (state == LIFE_MEDIUM)
		{
			mvwprintw(v->win_champions[i], 0, 0, "%ls", LIFE_MEDIUM_1);
			mvwprintw(v->win_champions[i], 1, 0, "%ls", LIFE_MEDIUM_2);
			mvwprintw(v->win_champions[i], 2, 0, "%ls", LIFE_MEDIUM_3);
			mvwprintw(v->win_champions[i], 3, 0, "%ls", LIFE_MEDIUM_4);
			mvwprintw(v->win_champions[i], 4, 0, "%ls", LIFE_MEDIUM_5);
			mvwprintw(v->win_champions[i], 5, 0, "%ls", LIFE_MEDIUM_6);
		}
		else if (state == LIFE_HIGH)
		{
			mvwprintw(v->win_champions[i], 0, 0, "%ls", LIFE_HIGH_1);
			mvwprintw(v->win_champions[i], 1, 0, "%ls", LIFE_HIGH_2);
			mvwprintw(v->win_champions[i], 2, 0, "%ls", LIFE_HIGH_3);
			mvwprintw(v->win_champions[i], 3, 0, "%ls", LIFE_HIGH_4);
			mvwprintw(v->win_champions[i], 4, 0, "%ls", LIFE_HIGH_5);
			mvwprintw(v->win_champions[i], 5, 0, "%ls", LIFE_HIGH_6);
		}
		else if (state == LIFE_FULL)
		{
			mvwprintw(v->win_champions[i], 0, 0, "%ls", LIFE_FULL_1);
			mvwprintw(v->win_champions[i], 1, 0, "%ls", LIFE_FULL_2);
			mvwprintw(v->win_champions[i], 2, 0, "%ls", LIFE_FULL_3);
			mvwprintw(v->win_champions[i], 3, 0, "%ls", LIFE_FULL_4);
			mvwprintw(v->win_champions[i], 4, 0, "%ls", LIFE_FULL_5);
			mvwprintw(v->win_champions[i], 5, 0, "%ls", LIFE_FULL_6);
		}
		wrefresh(v->win_champions[i]);
	}
}

void	maj_lifes(t_viewer *v)
{
	int i;
	int state;

	i = -1;
	while (++i < v->vm->nplayer)
	{
		if (!(v->anim_flags & (1 << i))
			&& v->vm->p[i].last_live_cycle <= (v->vm->ncycle - v->vm->ncycle_mod))
		{
			state = 100 * (v->vm->cycle_to_die - v->vm->ncycle_mod) / v->vm->cycle_to_die;
			if (state < LIFE_LOW)
				update_anim(v, i, LIFE_LOW);
			else if (state < LIFE_MEDIUM)
				update_anim(v, i, LIFE_MEDIUM);
			else if (state < LIFE_HIGH)
				update_anim(v, i, LIFE_HIGH);
			else
				update_anim(v, i, LIFE_FULL);
		}
	}
}

void	*th_render_routine(void *p_data)
{
	t_viewer	*v;

	v = (t_viewer *)p_data;
	pthread_mutex_lock(&v->mutex);
	init_arena(v);
	init_register(v);
	maj_process(v);
	maj_lifes(v);
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
			maj_lifes(v);
			/* mise à jour de l'arène */
			maj_arena(v);
			/* mise à jour des joueurs */
			maj_process(v);
			/* mise à jour des infos générales */
			mvwprintw(v->win_infos, 0, 69, "%-10d", v->vm->ncycle);
			mvwprintw(v->win_infos, 1, 69, "%-10d", v->vm->ncycle_mod);
			mvwprintw(v->win_infos, 2, 69, "%-10d", v->vm->cycle_to_die);
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
