/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:42:21 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/20 12:36:34 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWER_H
# define VIEWER_H
# include <libc.h>
# include "libft.h"
# include <ncurses.h>
# include <menu.h>
# include <pthread.h>
# include "corewar.h"
// # include "event.h"
# define KEY_FPS_LL 'p'
# define KEY_FPS_PP 'o'
# define KEY_LPF_LL 'k'
# define KEY_LPF_PP 'l'
# define KEY_PROCESS_LL 'i'
# define KEY_PROCESS_PP 'j'
# define KEY_PAUSE ' '
# define KEY_QUIT 'q'
# define FLAG_EVENT_CORE 1
# define FLAG_EVENT_TIMER 2
# define FLAG_EVENT_PAUSE 4
# define FLAG_EVENT_QUIT 8
// TODO mise a jour de win_infos en fonction des events
# define FLAG_KEY_EVENT_FPS 16
# define FLAG_KEY_EVENT_LPF 32
# define FLAG_KEY_EVENT_PAUSE 64
# define FLAG_KEY_EVENT_PROCESS 256


// " _ _"
// "| ' |"
// " \ /"
# define MSG_LIFE "LIFE"

// # define L1 "     "
// # define L2 "  -  "
// # define L3 "     "
//
// # define L1 "  _  "
// # define L2 " | | "
// # define L3 "  -  "
//
// # define L1 " ___ "
// # define L2 "|   |"
// # define L3 " --- "
//
// # define L1 " _ _ "
// # define L2 "|   |"
// # define L3 " -   "
//
// # define L1 "   _ "
// # define L2 "    |"
// # define L3 " -   "

# define ONOFF(x) ((x) ? "ON" : "OFF")

typedef struct s_vm	t_vm;

typedef struct		s_viewer
{
	unsigned char	arena[MEM_SIZE];
	unsigned char	arena_flag[MEM_SIZE]; // faire un cooldown pour que les modifs restents affichees plusieurs tours
	// char			events[4][100]; // useless
	WINDOW			*win_arena;
	WINDOW			*win_champions[4];
	WINDOW			*win_processes;
	WINDOW			*win_infos;

	int				process_offset;

	int				fps;
	int				lpf;

	pthread_mutex_t	mutex;
	pthread_cond_t	cond;

	pthread_t		th_core;
	pthread_t		th_render;
	pthread_t		th_input;
	pthread_t		th_timer;
	pthread_t		th_anim[4];

	int				event_flags;
	int				anim_flags;

	t_vm			*vm;

	t_list			*event_list;
}					t_viewer;

typedef struct		s_anim
{
	t_viewer		*v;
	int				i;
	char			*type;
}					t_anim;

WINDOW				*create_newwin(int height, int width, int starty, int startx, char *title);
void				destroy_win(WINDOW *local_win);

void				*th_core_routine(void *p_data);
void				*th_timer_routine(void *p_data);
void				*th_input_routine(void *p_data);
void				*th_render_routine(void *p_data);
void				*th_anim_routine(void *p_data);

void				new_anim(t_viewer *v, int i, const char *str);

void				viewer_init(t_viewer *v, t_vm *vm);
void				viewer_run(t_viewer *v);
void				maj_process(t_viewer *v);
void				maj_arena(t_viewer *v);

#endif
