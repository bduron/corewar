/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <bduron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:37:52 by bduron            #+#    #+#             */
/*   Updated: 2017/04/23 16:36:50 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void vm_init(t_vm *v)
{
	int i;

	ft_memset(v->a.arena, 0, sizeof(unsigned char) * MEM_SIZE);
	ft_memset(v->a.owner, -1, sizeof(char) * MEM_SIZE);
	ft_memset(v->a.type, -1, sizeof(char) * MEM_SIZE);
	v->process_lst = NULL;
	v->nprocess = 0;
	v->nprocess_alive = 0;
	v->ncycle = 0;
	v->ncycle_mod = 0;
	v->ncheck = 0;
	v->nlive_bctd = 0;
	v->cycle_to_die = CYCLE_TO_DIE;
	v->is_ctd_modified = 0;
	v->opt_flags = 0;
	v->dump_param = -1;
	v->verbose_param = 0;
	v->nplayer = 0;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		v->p[i].nplayer = 0;
		ft_memset(v->p[i].name, 0, PROG_NAME_LENGTH);
		ft_memset(v->p[i].comment, 0, COMMENT_LENGTH);
		ft_memset(v->p[i].code, 0, CHAMP_MAX_SIZE);
		i++;
	}
}
