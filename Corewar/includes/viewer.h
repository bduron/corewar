/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:42:21 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/13 16:06:28 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWER_H
# define VIEWER_H
# include <libc.h>
# include <ncurses.h>
# include <pthread.h>
# include "corewar.h"
# define KEY_FPS_LL 'p'
# define KEY_FPS_PP 'o'
# define KEY_LPF_LL 'k'
# define KEY_LPF_PP 'l'
# define KEY_PAUSE ' '
# define KEY_QUIT 'q'
# define FLAG_EVENT_CORE 1
# define FLAG_EVENT_TIMER 2
# define FLAG_EVENT_PAUSE 4
# define FLAG_EVENT_QUIT 8
# define ONOFF(x) ((x) ? "ON" : "OFF")

typedef struct
{
	char			events[4][100];
	WINDOW			*win_arena;
	WINDOW			*win_champions[4];
	WINDOW			*win_infos;

	int				fps;
	int				lpf;

	pthread_mutex_t	mutex;
	pthread_cond_t	cond;

	pthread_t		th_core;
	pthread_t		th_render;
	pthread_t		th_input;
	pthread_t		th_timer;

	int				event_flags;

	t_vm			*vm;
}	t_viewer;

WINDOW				*create_newwin(int height, int width, int starty, int startx, char *title);
void				destroy_win(WINDOW *local_win);

void				*th_core_routine(void *p_data);
void				*th_timer_routine(void *p_data);
void				*th_input_routine(void *p_data);
void				*th_render_routine(void *p_data);

void				viewer_init(t_viewer *v, t_vm *vm);
void				viewer_init_ncurses(t_viewer *v);
void				viewer_run(t_viewer *v);

#endif
