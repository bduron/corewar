/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:42:21 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/22 11:13:30 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWER_H
# define VIEWER_H
# include <libc.h>
# include <locale.h>
# include "libft.h"
# include "corewar.h"
# include <ncurses.h>
# include <menu.h>
# include <pthread.h>
# include "ressources.h"

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

# define FLAG_KEY_EVENT_FPS 16
# define FLAG_KEY_EVENT_LPF 32
# define FLAG_KEY_EVENT_PAUSE 64
# define FLAG_KEY_EVENT_PROCESS 256

# define LIFE_DEAD 0
# define LIFE_LOW 25
# define LIFE_MEDIUM 50
# define LIFE_HIGH 75
# define LIFE_FULL 100

# define ONOFF(x) ((x) ? "ON" : "OFF")
# define PRINT_CARRY (CARRY ? 'C' : ' ')
# define PRINT_LIVE (LIVE ? 'L' : ' ')

typedef struct s_vm	t_vm;
typedef struct s_process	t_process;

typedef struct		s_viewer
{
	unsigned char	arena[MEM_SIZE];
	char			owner[MEM_SIZE];
	int				arena_flag[MEM_SIZE];
	WINDOW			*win_arena;
	WINDOW			*win_title;
	WINDOW			*win_champions[MAX_PLAYERS];
	WINDOW			*win_processes;
	WINDOW			*win_register;
	WINDOW			*win_infos;
	int				process_selected;
	int				process_offset;
	char			anim_state[MAX_PLAYERS];
	int				fps;
	int				lpf;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	pthread_t		th_core;
	pthread_t		th_render;
	pthread_t		th_input;
	pthread_t		th_timer;
	pthread_t		th_anim[MAX_PLAYERS];
	int				event_flags;
	int				anim_flags;
	t_vm			*vm;
}					t_viewer;

typedef struct		s_anim
{
	t_viewer		*v;
	int				i;
}					t_anim;

/*
** vw_draw_life.c
*/
void				draw_life_full(t_viewer *v, int i);
void				draw_life_high(t_viewer *v, int i);
void				draw_life_medium(t_viewer *v, int i);
void				draw_life_low(t_viewer *v, int i);
void				draw_life_dead(t_viewer *v, int i);

/*
** vw_draw_others.c
*/
void				heal(t_viewer *v, int i);
void				draw_logo(t_viewer *v);

/*
** vw_init_win.c
*/
WINDOW				*create_newwin(int height, int width, int starty, int startx, char *title);
void				init_win_infos(t_viewer *v);
void				init_arena(t_viewer *v);
void				init_register(t_viewer *v);

/*
** vw_init.c
*/
void				viewer_init_colors();
void				viewer_init_ncurses(t_viewer *v);
void				viewer_init(t_viewer *v, t_vm *vm);
void				viewer_run(t_viewer *v);

/*
** vw_maj_win.c
*/
void				maj_register(t_viewer *v, t_process *process);
void				maj_arena(t_viewer *v);
void				maj_win_infos(t_viewer *v);
void				maj_process(t_viewer *v);

/*
** vw_th_anim.c
*/
void				*th_anim_routine(void *p_data);

/*
** vw_th_core.c
*/
void				*th_core_routine(void *p_data);

/*
** vw_th_input.c
*/
void				*th_input_routine(void *p_data);

/*
** vw_th_render.c
*/
void				*th_render_routine(void *p_data);

/*
** vw_th_timer.c
*/
void				*th_timer_routine(void *p_data);

#endif
