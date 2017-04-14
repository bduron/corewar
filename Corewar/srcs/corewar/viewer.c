/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolrajht <wolrajht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 15:20:09 by wolrajht          #+#    #+#             */
/*   Updated: 2017/04/14 11:13:11 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	viewer_init_colors()
{
	if (has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
}

static void	viewer_init_ncurses(t_viewer *v)
{
	int i;
	int win_arena_height;

	initscr();
	viewer_init_colors();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	curs_set(0);
	refresh();

	win_arena_height = LINES - (v->vm->nplayer * 3 + 6);
	v->win_arena = create_newwin(win_arena_height, COLS, 0, 0, "Arena");
	i = -1;
	while (++i < v->vm->nplayer)
		v->win_champions[i] = create_newwin(3, COLS, win_arena_height + 3 * i, 0, (char *)v->vm->p[i].name);
	v->win_infos = create_newwin(6, COLS, win_arena_height + v->vm->nplayer * 3, 0, "Informations");

	// v->win_arena = create_newwin(LINES / (v->vm->nplayer + 2), COLS, 0, 0, "Arena");
	// i = -1;
	// while (++i < v->vm->nplayer)
	// 	v->win_champions[i] = create_newwin(LINES / (v->vm->nplayer + 2), COLS,
	// 		(i + 1) * LINES / (v->vm->nplayer + 2), 0, (char *)v->vm->p[i].name);
	// v->win_infos = create_newwin(LINES / (v->vm->nplayer + 2), COLS,
	// 	(v->vm->nplayer + 1) * LINES / (v->vm->nplayer + 2), 0, "Informations");
}

void	viewer_init(t_viewer *v, t_vm *vm)
{
	v->vm = vm;
	v->lpf = 1;
	v->fps = 1048576;
	v->event_flags = 0;
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

WINDOW *create_newwin(int height, int width, int starty, int startx, char *title)
{
	WINDOW *win_box;
	WINDOW *win_content;
	size_t	len;

	win_box = newwin(height, width, starty, startx);
	box(win_box, 0 , 0);
	win_content = derwin(win_box, height - 2, width - 4, 1, 2);
	len = strlen(title);
	wmove(win_box, 0, (width - len) / 2 - 3);
	wprintw(win_box, " - %s - ", title);
	wrefresh(win_box);
	wrefresh(win_content);
	return (win_content);
}
