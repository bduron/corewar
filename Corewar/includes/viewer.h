/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:42:21 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/21 17:40:07 by pboutelo         ###   ########.fr       */
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
// TODO mise a jour de win_infos en fonction des events
# define FLAG_KEY_EVENT_FPS 16
# define FLAG_KEY_EVENT_LPF 32
# define FLAG_KEY_EVENT_PAUSE 64
# define FLAG_KEY_EVENT_PROCESS 256

# define FLAG_ANIM_0 1
# define FLAG_ANIM_25 2
# define FLAG_ANIM_50 4
# define FLAG_ANIM_75 8
# define FLAG_ANIM_100 16
# define FLAG_ANIM_HEAL 32

# define MSG_LIFE "LIFE"

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

# define LIFE_1_100 L"  ▓██▄ ▄██░"
# define LIFE_2_100 L" ▓█████████░"
# define LIFE_3_100 L"  ▓███████▒"
# define LIFE_4_100 L"  ░▒████▒░"
# define LIFE_5_100 L"    ░▐█░ "
# define LIFE_6_100 L""

# define LIFE_1_75 L"  ▓██▄ ▄██░"
# define LIFE_2_75 L" ▓█████ ▐██░"
# define LIFE_3_75 L"  ▓████▐██▒"
# define LIFE_4_75 L"  ░▒████▒░"
# define LIFE_5_75 L"    ░▐░░"
# define LIFE_6_75 L"      ░"

# define LIFE_1_50 L"  ▓██  ▄██░"
# define LIFE_2_50 L" ▓███▒   ██░"
# define LIFE_3_50 L"  ▓██░  ▐█▒"
# define LIFE_4_50 L"  ░▒███▐▒░"
# define LIFE_5_50 L"    ░▐░░░"
# define LIFE_6_50 L"     ░ ░"

# define LIFE_1_25 L"  ▓██░  ▄▄"
# define LIFE_2_25 L" ▓█▒░    ██░"
# define LIFE_3_25 L"  ░     ▐█▒"
# define LIFE_4_25 L"   ▒▐█ ▐▒░"
# define LIFE_5_25 L"    ░▐░ ░░"
# define LIFE_6_25 L"     ░  ░"

# define SKULL_1   L"  ▄▄▄▄▄▄"
# define SKULL_2   L" ▄▀██▀▀███"
# define SKULL_3   L" ▐ ▐█░ ▐██░"
# define SKULL_4   L" ░█▄▄███▒░"
# define SKULL_5   L"  ░███ ░░"
# define SKULL_6   L" ░ ░    ░"

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

	int				fps;
	int				lpf;

	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_anim[MAX_PLAYERS];
	pthread_cond_t	cond;
	// pthread_cond_t	cond_anim[MAX_PLAYERS];

	pthread_t		th_core;
	pthread_t		th_render;
	pthread_t		th_input;
	pthread_t		th_timer;
	pthread_t		th_anim[MAX_PLAYERS];

	char			event_flags;
	char			anim_flags[MAX_PLAYERS];

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

void				viewer_init(t_viewer *v, t_vm *vm);
void				viewer_run(t_viewer *v);
void				maj_process(t_viewer *v);
void				maj_arena(t_viewer *v);

#endif
