/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <bduron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 17:16:21 by bduron            #+#    #+#             */
/*   Updated: 2017/04/19 16:43:09 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** bctd = Between CYCLES_TO_DIE
*/

#ifndef COREWAR_H
# define COREWAR_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include "op.h"
# include "viewer.h"
# include <stdio.h> // to be removed

# define COREWAR_EXEC_MAGIC_L 0xf383ea
# define ARENA(x)	v->a.arena[(unsigned int)(x) % MEM_SIZE]
# define OWNER(x)	v->a.owner[(unsigned int)(x) % MEM_SIZE]
/*
** pboutelo
** proposition :
**     # define PC process->pc à la place
** cast du t_list dans les appels de fonction, pour éviter de caster n fois...
*/
# define PC			(((t_process *)process->content)->pc)
# define CARRY		(((t_process *)process->content)->carry)
# define REG		(((t_process *)process->content)->reg)
# define NEXT_OP	(((t_process *)process->content)->next_op)
# define OP_CAST	(((t_process *)process->content)->op_cast)
# define LIVE		(((t_process *)process->content)->live_count)
# define BCTD		v->ncycle_mod % v->cycle_to_die == 0 && v->ncycle_mod != 0
# define B_OCT		(ARENA(PC + 1))

# define OCT_03(x)	(x & 0b11)
# define OCT_02(x)	((x & 0b1100) >> 2)
# define OCT_01(x)	((x & 0b110000) >> 4)
# define OCT_00(x)	((x & 0b11000000) >> 6)

typedef struct		s_arena
{
	unsigned char	arena[MEM_SIZE];
	char			owner[MEM_SIZE];
	char			type[MEM_SIZE];
}					t_arena;

typedef struct		s_process
{
	int				carry;
	int				reg[REG_NUMBER];
	int				pc;
	int				op_cast; // launch op when cast == 0
	int				live_count;	// count emitted lives between CYCLE_TO_DIE
	unsigned char	next_op;
}					t_process;

typedef struct		s_player
{
	int				nplayer;
	unsigned char	name[PROG_NAME_LENGTH + 1];
	unsigned char	comment[COMMENT_LENGTH + 1];
	unsigned char	code[CHAMP_MAX_SIZE];
	int				prog_len;
	int				exec_magic;
	int				pc_address;
	int 			nblive;
}					t_player;

typedef struct		s_vm
{
	t_list			*process_lst;
	t_arena			a;
	t_player		p[MAX_PLAYERS];
	int				nplayer;
	int				nprocess;
	int				last_live_id;
	int				ncycle;
	int				ncycle_mod;
	int				nlive_bctd; // lives emitted bctd
	int				cycle_to_die; // Decrement under certain conditions
	int				ncheck; // nb ctd in a row w/o decrementing ctd
	int				is_ctd_modified;
	int				display_mode; // pboutelo: 1: raw, 2: interactive
}					t_vm;

void is_player(t_vm *v, int live);
void save_player(char *file, t_vm *v, int i);
void get_players(int argc, char **argv, t_vm *v);
int is_corewar_execmagic(char *file);
int get_prog_size(char *file);
int is_valid_player(char *file);
int is_cor_file(char *file);
void load_arena(t_vm *v);
void load_champions(t_vm *v);
void load_processes(t_vm *v);
void vm_init(t_vm *v);
void vm_free(t_vm *v);

void	run_game(t_vm *v);
void 	browse_processes_lst(t_vm *v);
void	operate_process(t_vm *v, t_list *process);
void	print_reg(t_vm *v, t_list *process, unsigned int val, int addr);
int		get_ar(t_vm *v, t_list *process, u_char *shift, u_char type);
void	octal_shift(t_list *process, u_char n, u_char label_size, u_char arg_nb);
int		reverse_bytes(unsigned char *addr, int nbytes);
int		check_arg(u_char arg, u_char n, u_char arg_nb);
void	add_process(t_vm *v, t_list *process, unsigned int son_pc);

void xerror(char *error_msg, int error_id); // move to libft

/*** debug ***/
void dump(t_player p);
void print_arena(t_vm *v);
void test_print_v(t_vm *v, int argc);
void print_processes(t_vm *v);

#endif
