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

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"

typedef struct	s_process
{
	int carry;
	int reg[REG_NUMBER];	
	int pc;
	

}				t_process;

typedef struct	s_vm
{
	t_list			*process_lst;
	unsigned char	arena[MEM_SIZE];
	t_player		player_lst[MAX_PLAYERS];
	char			last_live_id;




}				t_vm;

typedef struct	s_player;
{
	int				nplayer;
	char			champion[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	unsigned char	*champ_code;
}				t_player;

#endif
