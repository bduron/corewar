/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vw_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolrajht <wolrajht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 15:20:09 by wolrajht          #+#    #+#             */
/*   Updated: 2017/04/22 19:34:14 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

void	viewer_init_colors(void)
{
	if (has_colors() == FALSE)
	{
		endwin();
		xerror("Your terminal does not support color\n", -33);
	}
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_WHITE);
	init_pair(9, COLOR_BLACK, COLOR_RED);
	init_pair(10, COLOR_BLACK, COLOR_GREEN);
	init_pair(11, COLOR_BLACK, COLOR_BLUE);
	init_pair(12, COLOR_BLACK, COLOR_YELLOW);
	init_pair(13, COLOR_BLACK, COLOR_CYAN);
	init_pair(14, COLOR_BLACK, COLOR_MAGENTA);
}

void	viewer_init_ncurses(t_viewer *v)
{
	int i;

	initscr();
	viewer_init_colors();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	curs_set(0);
	refresh();
	v->win_arena = create_newwin((int[4]){ARENA_L, ARENA_C, 0, 0}, ARENA_NAME);
	v->win_title = create_newwin((int[4]){TITLE_L, TITLE_C, 0, ARENA_C},
		TITLE_NAME);
	v->win_processes = create_newwin((int[4]){PROCS_L, PROCS_C, TITLE_L,
		ARENA_C}, PROCS_NAME);
	v->win_register = create_newwin((int[4]){REGIS_L, REGIS_C, TITLE_L
		+ PROCS_L, ARENA_C}, REGIS_NAME);
	v->win_infos = create_newwin((int[4]){INFOS_L, INFOS_C, ARENA_L, 0},
		INFOS_NAME);
	i = -1;
	while (++i < v->vm->nplayer)
		v->win_champions[i] = create_newwin((int[4]){CHAMP_L, CHAMP_C,
			LINES - (CHAMP_L), ARENA_C + i * CHAMP_C},
			(char *)v->vm->p[i].name);
	draw_logo(v);
	wrefresh(v->win_title);
}

void	viewer_init(t_viewer *v, t_vm *vm)
{
	setlocale(LC_ALL, "");
	v->vm = vm;
	vm->v = v;
	v->lpf = 1;
	v->fps = 1048576;
	v->event_flags |= FLAG_EVENT_PAUSE;
	v->anim_flags = 0;
	v->credits_flag = 0;
	v->process_selected = 0;
	v->process_offset = 0;
	ft_memset(v->anim_state, 101, sizeof(char) * MAX_PLAYERS);
	ft_memset(v->arena_flag, 0, sizeof(int) * MEM_SIZE);
	pthread_mutex_init(&v->mutex, NULL);
	pthread_cond_init(&v->cond, NULL);
	viewer_init_ncurses(v);
}

void	viewer_run(t_viewer *v)
{
	void *ret;

	if (pthread_create(&v->th_render, NULL, &th_render_routine, v) < 0)
		xerror("pthread_create error for th_render\n", -33);
	if (pthread_create(&v->th_core, NULL, &th_core_routine, v) < 0)
		xerror("pthread_create error for th_core\n", -33);
	if (pthread_create(&v->th_input, NULL, &th_input_routine, v) < 0)
		xerror("pthread_create error for th_input\n", -33);
	if (pthread_create(&v->th_timer, NULL, &th_timer_routine, v) < 0)
		xerror("pthread_create error for th_timer\n", -33);
	(void)pthread_join(v->th_core, &ret);
	(void)pthread_join(v->th_input, &ret);
	(void)pthread_join(v->th_render, &ret);
	(void)pthread_join(v->th_timer, &ret);
	endwin();
}
