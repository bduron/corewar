/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_viewer.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:42:21 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/12 18:49:44 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VIEWER_H
# define COREWAR_VIEWER_H
# include <libc.h>
# include <ncurses.h>
# include <pthread.h>
# include "sem_port.h"
# define FPS_LL 'o'
# define FPS_PP 'p'
# define LPF_LL 'k'
# define LPF_PP 'l'

typedef struct		s_viewer
{
	char			arena[1024];
	char			*names[4];
	char			events[4][100];
	WINDOW			*win_arena;
	WINDOW			*win_champions[4];
	WINDOW			*win_infos;
	t_sem_port		sem_coreDone;
	t_sem_port		sem_ready2core;
	t_sem_port		sem_show;
	t_sem_port		sem_pause;
	t_sem_port		sem_sleepDone;
	t_sem_port		sem_ready2sleep;
	char			flag_pause;
	int				fps;
	int				lpf;
	int				input;
}					t_viewer;

WINDOW				*create_newwin(int height, int width, int starty, int startx, char *name);
void				destroy_win(WINDOW *local_win);

void				*th_core_routine(void *p_data);
void				*th_timer_routine(void *p_data);
void				*th_input_routine(void *p_data);
void				*th_render_routine(void *p_data);

#endif
