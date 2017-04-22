/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vw_init_win.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 10:12:32 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/22 11:02:56 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

WINDOW *create_newwin(int height, int width, int starty, int startx, char *title)
{
	WINDOW *win_box;
	WINDOW *win_content;
	// size_t	len;
	(void)title;

	win_box = newwin(height, width, starty, startx);
	// box(win_box, 0 , 0);
	wborder(win_box, ACS_RTEE, ACS_LTEE, ACS_BTEE, ACS_TTEE, ACS_ULCORNER,
		ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	win_content = derwin(win_box, height - 2, width - 4, 1, 2);
	// len = strlen(title);
	// wmove(win_box, 0, (width - len) / 2 - 3);
	// wprintw(win_box, " - %s - ", title);
	wrefresh(win_box);
	wrefresh(win_content);
	return (win_content);
}

void	init_win_infos(t_viewer *v)
{
	werase(v->win_infos);
	mvwprintw(v->win_infos, 0, 0, "FPS:              "
		"CONTROLS: [ << '%c' ] [ '%c' >> ]", KEY_FPS_PP, KEY_FPS_LL);
	mvwprintw(v->win_infos, 1, 0, "LPF:              "
		"CONTROLS: [ << '%c' ] [ '%c' >> ]", KEY_LPF_LL, KEY_LPF_PP);
	mvwprintw(v->win_infos, 2, 0, "PAUSE:            "
		"CONTROLS: [ '%c' ]", KEY_PAUSE);
	mvwprintw(v->win_infos, 3, 0, "QUIT:             "
		"CONTROLS: [ '%c' ]", KEY_QUIT);
	mvwprintw(v->win_infos, 0, 55, "CYCLE:");
	mvwprintw(v->win_infos, 1, 55, "CYCLE_MOD:");
	mvwprintw(v->win_infos, 2, 55, "CYCLE_TO_DIE:");
	wrefresh(v->win_infos);
}

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
			mvwprintw(v->win_register, 2 * (i - (REG_NUMBER / 2)), 31,
				"Register[%3d] = %13d", i, 0);
	}
	wrefresh(v->win_register);
}
