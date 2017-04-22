/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vw_maj_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 10:37:24 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/22 18:28:37 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

void		maj_register(t_viewer *v, t_process *process)
{
	int i;

	i = -1;
	while (++i < REG_NUMBER)
	{
		if (i < REG_NUMBER / 2)
			mvwprintw(v->win_register, 2 * i, 16, "%13d", process->reg[i]);
		else
			mvwprintw(v->win_register, 2 * (i - (REG_NUMBER / 2)), 46, "%13d",
				process->reg[i]);
	}
	wrefresh(v->win_register);
}

static void	maj_arena_print_byte(t_viewer *v, int i)
{
	if (v->arena[i] != v->vm->a.arena[i]
		|| v->owner[i] != v->vm->a.owner[i])
	{
		wattron(v->win_arena, A_BOLD);
		wattron(v->win_arena, COLOR_PAIR(v->vm->a.owner[i] + 2));
		mvwprintw(v->win_arena, i / 64, (i % 64 * 3), "%.2x",
			v->vm->a.arena[i]);
		v->arena[i] = v->vm->a.arena[i];
		v->owner[i] = v->vm->a.owner[i];
		v->arena_flag[i] = v->vm->ncycle + 50;
		wattroff(v->win_arena, COLOR_PAIR(v->vm->a.owner[i] + 2));
		wattroff(v->win_arena, A_BOLD);
	}
	else if (v->arena_flag[i] && v->arena_flag[i] < v->vm->ncycle)
	{
		wattron(v->win_arena, COLOR_PAIR(v->vm->a.owner[i] + 2));
		mvwprintw(v->win_arena, i / 64, (i % 64 * 3), "%.2x",
			v->vm->a.arena[i]);
		wattroff(v->win_arena, COLOR_PAIR(v->vm->a.owner[i] + 2));
		v->arena_flag[i] = 0;
	}
}

void		maj_arena(t_viewer *v)
{
	int	i;

	i = -1;
	while (++i < MEM_SIZE)
		maj_arena_print_byte(v, i);
	wrefresh(v->win_arena);
}

void		maj_infos_input(t_viewer *v)
{
	mvwprintw(v->win_infos, 1, 19, "%10d", 1048576 / v->fps);
	mvwprintw(v->win_infos, 2, 19, "%10d", v->lpf);
	mvwprintw(v->win_infos, 4, 19, "%10s",
		ONOFF(v->event_flags & FLAG_EVENT_PAUSE));
	wrefresh(v->win_infos);
}

void		maj_infos_cycle(t_viewer *v)
{
	mvwprintw(v->win_infos, 1, 114, "%10d", v->vm->ncycle);
	mvwprintw(v->win_infos, 2, 114, "%10d", v->vm->ncycle_mod);
	mvwprintw(v->win_infos, 3, 114, "%10d", v->vm->cycle_to_die);
	wrefresh(v->win_infos);
}
