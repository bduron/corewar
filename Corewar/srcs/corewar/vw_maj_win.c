/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vw_maj_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 10:37:24 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/22 11:03:02 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

void	maj_win_infos(t_viewer *v)
{
	mvwprintw(v->win_infos, 0, 7, "%-10d", 1048576 / v->fps);
	mvwprintw(v->win_infos, 1, 7, "%-10d", v->lpf);
	mvwprintw(v->win_infos, 2, 7, "%-10s", ONOFF(v->event_flags & FLAG_EVENT_PAUSE));
	wrefresh(v->win_infos);
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
			mvwprintw(v->win_processes, i - v->process_offset, 0, "#%-5d %2dx%-2d [%c][%c]: ", NPRO, PC / 64 + 1, PC % 64 + 1, PRINT_LIVE, PRINT_CARRY);
			if (NEXT_OP >= 0 && NEXT_OP < 16)
				mvwprintw(v->win_processes, i - v->process_offset, 20, "          will cast a \"%5s\" in %4d laps.", op_tab[NEXT_OP].name, OP_CAST);
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
