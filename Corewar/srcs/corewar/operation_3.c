/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <bduron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:54:01 by bduron            #+#    #+#             */
/*   Updated: 2017/04/20 18:49:55 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_zjmp(t_vm *v, t_list *process)
{
	int shift;

	shift = reverse_bytes(v, PC + 1, 2);
	shift %= IDX_MOD;
	PC = CARRY == 1 ? (unsigned int)(PC + shift) % MEM_SIZE : (PC + 3) % MEM_SIZE;
	if (v->display_mode == 1)
	{
		printf("P%5d | zjmp %d ", NPRO, shift);
		if (CARRY)
			printf("OK\n");
		else
			printf("FAILED\n");
	}
}

void	op_fork(t_vm *v, t_list *process)
{
	int shift;

	shift = reverse_bytes(v, PC + 1, 2);
	shift %= IDX_MOD;
	if (v->display_mode == 1)
	{
		printf("P%5d | fork %d (%d)\n", NPRO, shift, (unsigned int)(PC + shift) % MEM_SIZE);
		print_adv(v, process, 3);
	}
	add_process(v, process, (unsigned int)(PC + shift) % MEM_SIZE);
	PC += 3;
	PC %= MEM_SIZE;
}

void	op_lfork(t_vm *v, t_list *process)
{
	int shift;

	shift = reverse_bytes(v, PC + 1, 2);
	if (v->display_mode == 1)
	{
		printf("P%5d | lfork %d (%d)\n", NPRO, shift, (unsigned int)(PC + shift) % MEM_SIZE);
		print_adv(v, process, 3);
	}
	add_process(v, process, (unsigned int)(PC + shift) % MEM_SIZE);
	PC += 3;
	PC %= MEM_SIZE;
}