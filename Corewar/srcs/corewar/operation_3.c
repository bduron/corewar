/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:54:01 by bduron            #+#    #+#             */
/*   Updated: 2017/04/19 19:54:05 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_zjmp(t_vm *v, t_list *process)
{
	int shift;

	shift = reverse_bytes(&ARENA(PC + 1), 2);
	shift %= IDX_MOD;
	PC = CARRY == 1 ? (unsigned int)(PC + shift) % MEM_SIZE : (PC + 3) % MEM_SIZE;
	if (v->display_mode == 1)
	{
		printf("zjmp %d ", shift);
		if (CARRY)
			printf("OK\n");
		else
			printf("FAILED\n");
	}
}

void	op_fork(t_vm *v, t_list *process)
{
	int shift;

	shift = reverse_bytes(&ARENA(PC + 1), 2);
	shift %= IDX_MOD;
	if (v->display_mode == 1)
		printf("fork %d\n", shift);
	add_process(v, process, (unsigned int)(PC + shift) % MEM_SIZE);
	PC += 3;
	PC %= MEM_SIZE;
}

void	op_lfork(t_vm *v, t_list *process)
{
	int shift;

	shift = reverse_bytes(&ARENA(PC + 1), 2);
	if (v->display_mode == 1)
		printf("fork %d\n", shift);
	add_process(v, process, (unsigned int)(PC + shift) % MEM_SIZE);
	PC += 3;
	PC %= MEM_SIZE;
}
