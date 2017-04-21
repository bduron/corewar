/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:42:21 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/21 20:02:59 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEWER_H
# define VIEWER_H
# include <libc.h>
# include <locale.h>
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
# define PRINT_NEXT_OP ((NEXT_OP >= 0 && NEXT_OP < 16) ? op_tab[NEXT_OP].name : "")
# define PRINT_CARRY (CARRY ? 'C' : ' ')
# define PRINT_LIVE (LIVE ? 'L' : ' ')

# define LOGO_1  L"  ▄████▄   ▒█████   ██▀███  ▓█████  █     █░ ▄▄▄       ██▀███  "
# define LOGO_2  L" ▒██▀ ▀█  ▒██▒  ██▒▓██ ▒ ██▒▓█   ▀ ▓█░ █ ░█░▒████▄    ▓██ ▒ ██▒"
# define LOGO_3  L" ▒▓█    ▄ ▒██░  ██▒▓██ ░▄█ ▒▒███   ▒█░ █ ░█ ▒██  ▀█▄  ▓██ ░▄█ ▒"
# define LOGO_4  L" ▒▓▓▄ ▄██▒▒██   ██░▒██▀▀█▄  ▒▓█  ▄ ░█░ █ ░█ ░██▄▄▄▄██ ▒██▀▀█▄  "
# define LOGO_5  L" ▒ ▓███▀ ░░ ████▓▒░░██▓ ▒██▒░▒████▒░░██▒██▓  ▓█   ▓██▒░██▓ ▒██▒"
# define LOGO_6  L" ░ ░▒ ▒  ░░ ▒░▒░▒░ ░ ▒▓ ░▒▓░░░ ▒░ ░░ ▓░▒ ▒   ▒▒   ▓▒█░░ ▒▓ ░▒▓░"
# define LOGO_7  L"   ░  ▒     ░ ▒ ▒░   ░▒ ░ ▒░ ░ ░  ░  ▒ ░ ░    ▒   ▒▒ ░  ░▒ ░ ▒░"
# define LOGO_8  L" ░        ░ ░ ░ ▒    ░░   ░    ░     ░   ░    ░   ▒     ░░   ░ "
# define LOGO_9  L" ░ ░          ░ ░     ░        ░  ░    ░          ░  ░   ░     "
# define LOGO_10 L" ░                          2016 pboutelo kcosta bduron cpoulet"

# define LIFE_FULL_1 L"  ▓██▄ ▄██░"
# define LIFE_FULL_2 L" ▓█████████░"
# define LIFE_FULL_3 L"  ▓███████▒"
# define LIFE_FULL_4 L"  ░▒████▒░"
# define LIFE_FULL_5 L"    ░▐█░ "
# define LIFE_FULL_6 L""

# define LIFE_HIGH_1 L"  ▓██▄ ▄██░"
# define LIFE_HIGH_2 L" ▓█████ ▐██░"
# define LIFE_HIGH_3 L"  ▓████▐██▒"
# define LIFE_HIGH_4 L"  ░▒████▒░"
# define LIFE_HIGH_5 L"    ░▐░░"
# define LIFE_HIGH_6 L"      ░"

# define LIFE_MEDIUM_1 L"  ▓██  ▄██░"
# define LIFE_MEDIUM_2 L" ▓███▒   ██░"
# define LIFE_MEDIUM_3 L"  ▓██░  ▐█▒"
# define LIFE_MEDIUM_4 L"  ░▒███▐▒░"
# define LIFE_MEDIUM_5 L"    ░▐░░░"
# define LIFE_MEDIUM_6 L"     ░ ░"

# define LIFE_LOW_1 L"  ▓██░  ▄▄"
# define LIFE_LOW_2 L" ▓█▒░    ██░"
# define LIFE_LOW_3 L"  ░     ▐█▒"
# define LIFE_LOW_4 L"   ▒▐█ ▐▒░"
# define LIFE_LOW_5 L"    ░▐░ ░░"
# define LIFE_LOW_6 L"     ░  ░"

# define SKULL_1 L"   ▄▄▄▄▄▄"
# define SKULL_2 L" ▄▀██▀▀███"
# define SKULL_3 L" ▐ ▐█░ ▐██░"
# define SKULL_4 L" ░█▄▄███▒░"
# define SKULL_5 L"  ░███ ░░"
# define SKULL_6 L" ░ ░    ░"


# define SKULL_1 L"   ▄    ▄"
# define SKULL_2 L" ▐█      ██"
# define SKULL_3 L"░██       ▐██░"
# define SKULL_4 L"  ██▄     █▀▒░"
# define SKULL_5 L"   ▀█▐█▄ █░"
# define SKULL_6 L"  ░   ▄▀▐▄   ░"


# define SKULL_1 L" ░  ▄░  ░"
# define SKULL_2 L"   ░██░░"
# define SKULL_3 L"▄▄▄▐███▄▄▄"
# define SKULL_4 L" ░░▄███▄░"
# define SKULL_5 L"  ░█▀░░▀▄"
# define SKULL_6 L""

typedef struct s_vm	t_vm;

typedef struct		s_viewer
{
	unsigned char	arena[MEM_SIZE];
	char			owner[MEM_SIZE];
	int				arena_flag[MEM_SIZE]; // faire un cooldown pour que les modifs restents affichees plusieurs tours
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

WINDOW				*create_newwin(int height, int width, int starty, int startx, char *title);
void				destroy_win(WINDOW *local_win);

void				*th_core_routine(void *p_data);
void				*th_timer_routine(void *p_data);
void				*th_input_routine(void *p_data);
void				*th_render_routine(void *p_data);
void				*th_anim_routine(void *p_data);

void				new_anim(t_viewer *v, int i);

void				viewer_init(t_viewer *v, t_vm *vm);
void				viewer_run(t_viewer *v);
void				maj_process(t_viewer *v);
void				maj_arena(t_viewer *v);

#endif
