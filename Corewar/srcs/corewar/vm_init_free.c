/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:37:52 by bduron            #+#    #+#             */
/*   Updated: 2017/03/21 17:39:59 by bduron           ###   ########.fr       */
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

void vm_free(t_vm *v)
{
	(void)v;
}
