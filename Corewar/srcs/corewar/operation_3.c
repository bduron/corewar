/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <cpoulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:33:45 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/19 19:15:29 by cpoulet          ###   ########.fr       */
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
		printf("PC PARENT : %d\t", PC);
	add_process(v, process, (unsigned int)(PC + shift) % MEM_SIZE);
	PC += 3;
	PC %= MEM_SIZE;
	if (v->display_mode == 1)
		printf("PC ENFANT : %d\n", (unsigned int)(PC + shift) % MEM_SIZE);
}

void	op_lfork(t_vm *v, t_list *process)
{
	int shift;

	shift = reverse_bytes(&ARENA(PC + 1), 2);
	if (v->display_mode == 1)
		printf("PC PARENT : %d\t", PC);
	add_process(v, process, (unsigned int)(PC + shift) % MEM_SIZE);
	PC += 3;
	PC %= MEM_SIZE;
	if (v->display_mode == 1)
		printf("PC ENFANT : %d\n", (unsigned int)(PC + shift) % MEM_SIZE);
}
