/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vw_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolrajht <wolrajht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 15:20:09 by wolrajht          #+#    #+#             */
/*   Updated: 2017/04/22 11:03:56 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	viewer_init_colors()
{
	if (has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_WHITE);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	init_pair(9, COLOR_BLACK, COLOR_GREEN);
	init_pair(10, COLOR_BLACK, COLOR_BLUE);
	init_pair(11, COLOR_BLACK, COLOR_YELLOW);
	init_pair(12, COLOR_BLACK, COLOR_CYAN);
}

void	viewer_init_ncurses(t_viewer *v)
{
	int register_height;

	initscr();
	viewer_init_colors();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	curs_set(0);
	refresh();

	if (REG_NUMBER % 2)
		register_height = REG_NUMBER + 2;
	else
		register_height = REG_NUMBER + 1;
	v->win_arena = create_newwin(LINES - 6, COLS - 68, 0, 0, "Arena");
	v->win_title = create_newwin(12, 68, 0, COLS - 68, "Title");
	v->win_processes = create_newwin(LINES - (12 + register_height + 8 + 6), 68, 12, COLS - 68, "Processes list");
	v->win_register = create_newwin(register_height, 68, LINES - 8 - 6 - (register_height), COLS - 68, "Register");
	v->win_champions[0] = create_newwin(8, 17, LINES - 8 - 6, COLS - 68, (char *)v->vm->p[0].name);
	v->win_champions[1] = create_newwin(8, 17, LINES - 8 - 6, COLS - 51, (char *)v->vm->p[1].name);
	v->win_champions[2] = create_newwin(8, 17, LINES - 8 - 6, COLS - 34, (char *)v->vm->p[2].name);
	v->win_champions[3] = create_newwin(8, 17, LINES - 8 - 6, COLS - 17, (char *)v->vm->p[3].name);
	v->win_infos = create_newwin(6, COLS, LINES - 6, 0, "Informations");
	draw_logo(v);
	wrefresh(v->win_title);
}

void	viewer_init(t_viewer *v, t_vm *vm)
{
	setlocale (LC_ALL,"");
	v->vm = vm;
	vm->v = v;
	v->lpf = 1;
	v->fps = 1048576;
	v->event_flags |= FLAG_EVENT_PAUSE;
	v->process_selected = 0;
	v->process_offset = 0;
	v->anim_flags = 0;
	ft_memset(v->anim_state, 101, sizeof(char) * MAX_PLAYERS);
	ft_memset(v->arena_flag, 0, sizeof(int) * MEM_SIZE);
	pthread_mutex_init(&v->mutex, NULL);
	pthread_cond_init(&v->cond, NULL);
	viewer_init_ncurses(v);
}

void	viewer_run(t_viewer *v)
{
	void *ret;

	if (pthread_create(&v->th_render, NULL, &th_render_routine, v) < 0) {
		fprintf(stderr, "pthread_create error for th_render\n");
		exit(1);
	}
	if (pthread_create(&v->th_core, NULL, &th_core_routine, v) < 0) {
		fprintf(stderr, "pthread_create error for th_core\n");
		exit(1);
	}
	if (pthread_create(&v->th_input, NULL, &th_input_routine, v) < 0) {
		fprintf(stderr, "pthread_create error for th_input\n");
		exit(1);
	}
	if (pthread_create(&v->th_timer, NULL, &th_timer_routine, v) < 0) {
		fprintf(stderr, "pthread_create error for th_timer\n");
		exit(1);
	}
	(void)pthread_join(v->th_core, &ret);
	(void)pthread_join(v->th_input, &ret);
	(void)pthread_join(v->th_render, &ret);
	(void)pthread_join(v->th_timer, &ret);
	endwin();
}
