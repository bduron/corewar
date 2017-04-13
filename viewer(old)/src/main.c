/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:41:16 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/13 15:28:16 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_viewer.h"

int main(void)
{
	t_viewer	v;
	pthread_t	th_core, th_render, th_input, th_timer;
	void		*ret;
	int			i;

	v.names[0] = "Wolfgang junior";
	v.names[1] = "Mc Ron";
	v.names[2] = "Eude Herbert";
	v.names[3] = "Jacques-Henri";

	v.lpf = 1;
	v.fps = 1048576;

	pthread_mutex_init(&v.mutex, NULL);
	pthread_cond_init(&v.cond, NULL);

	v.event_flags = 0;

	bzero(v.arena, 1024);

	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	curs_set(0);
	refresh();

	v.win_arena = create_newwin(LINES / 6, COLS, 0, 0, "Arena");
	i = -1;
	while (++i < 4)
		v.win_champions[i] = create_newwin(LINES / 6, COLS, (i + 1) * LINES / 6, 0, v.names[i]);
	v.win_infos = create_newwin(LINES / 6, COLS, 5 * LINES / 6, 0, "Informations");

	// v.win_arena = create_newwin(32, (32 + 2) * 2, 0, 0, "Arena");
	// i = -1;
	// while (++i < 1024)
	// 	mvwprintw(v.win_arena, i / 32, (i % 32) * 2, "%x", v.arena[i] % 256);
	// wrefresh(v.win_arena);
	// i = -1;
	// while (++i < 4)
	// 	v.win_champions[i] = create_newwin(LINES - 32, (32 + 2) * 2 / 4, 32, i * (32 + 2) * 2 / 4, v.names[i]);
	// v.win_infos = create_newwin(LINES, COLS - (32 + 2) * 2, 0, (32 + 2) * 2, "Informations");

	// v.win_arena = create_newwin(LINES - 10, 2 * (LINES - 10), 0, 0, "Arena");
	// i = -1;
	// while (++i < 4096)
	// 	mvwprintw(v.win_arena, i / 64, (i % 64) * 2, "%x", i % 256);
	// wrefresh(v.win_arena);
	// i = -1;
	// while (++i < 4)
	// 	v.win_champions[i] = create_newwin(10, 2 * (LINES - 10) / 4, LINES - 10, i * 2 * (LINES - 10) / 4, v.names[i]);
	// v.win_infos = create_newwin(LINES, COLS - 2 * (LINES - 10), 0, 2 * (LINES - 10), "Informations");

	if (pthread_create(&th_render, NULL, &th_render_routine, &v) < 0) {
		fprintf(stderr, "pthread_create error for th_render\n");
		exit(1);
	}

	if (pthread_create(&th_core, NULL, &th_core_routine, &v) < 0) {
		fprintf(stderr, "pthread_create error for th_core\n");
		exit(1);
	}

	if (pthread_create(&th_input, NULL, &th_input_routine, &v) < 0) {
		fprintf(stderr, "pthread_create error for th_input\n");
		exit(1);
	}

	if (pthread_create(&th_timer, NULL, &th_timer_routine, &v) < 0) {
		fprintf(stderr, "pthread_create error for th_timer\n");
		exit(1);
	}



	(void)pthread_join(th_core, &ret);
	(void)pthread_join(th_input, &ret);
	(void)pthread_join(th_render, &ret);
	(void)pthread_join(th_timer, &ret);

	endwin();

	return (0);
}

WINDOW *create_newwin(int height, int width, int starty, int startx, char *name)
{
	WINDOW *win_box;
	WINDOW *win_content;
	size_t	len;

	win_box = newwin(height, width, starty, startx);
	box(win_box, 0 , 0);
	win_content = derwin(win_box, height - 2, width - 4, 1, 2);
	len = strlen(name);
	wmove(win_box, 0, (width - len) / 2 - 3);
	wprintw(win_box, " - %s - ", name);
	wrefresh(win_box);
	wrefresh(win_content);
	return (win_content);
}
