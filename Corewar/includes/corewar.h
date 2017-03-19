/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 17:16:21 by bduron            #+#    #+#             */
/*   Updated: 2017/03/17 17:54:46 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** bctd = Between CYCLES_TO_DIE
*/

#ifndef COREWAR_H
# define COREWAR_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
# include "libft.h"
# include "op.h"

# define COREWAR_EXEC_MAGIC_L 0xf383ea

typedef struct	s_process
{
	int carry;
	int reg[REG_NUMBER];	
	int pc;
	int op_cast; // launch op when cast == 0 
	int live_count;	// count emitted lives between CYCLE_TO_DIE 	


}				t_process;

typedef struct	s_player
{
	int				nplayer;
	unsigned char	name[PROG_NAME_LENGTH + 1];
	unsigned char	comment[COMMENT_LENGTH + 1];
	unsigned char	code[CHAMP_MAX_SIZE];
	int				prog_len;
	int				exec_magic;
}				t_player;

typedef struct	s_vm
{
	t_list			*process_lst;
	unsigned char	arena[MEM_SIZE];
	t_player		p[MAX_PLAYERS];
	int				nplayer;		
	int				last_live_id;
	int				ncycle;		
	int				nlive_bctd; // lives emitted bctd
	int				cycle_to_die; // Decrement under certain conditions
	int				ncheck_bctd; // nb ctd in a row w/o decrementing ctd		



}				t_vm;


void save_player(char *file, t_vm *v, int i);
void get_players(int argc, char **argv, t_vm *v);
int is_corewar_execmagic(char *file);
int get_prog_size(char *file);
int is_valid_player(char *file);
int is_cor_file(char *file);
void vm_init(t_vm *v);
void vm_free(t_vm *v);

void xerror(char *error_msg, int error_id); // move to libft

#endif
