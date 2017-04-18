/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <cpoulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:33:45 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/18 17:56:06 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_zjmp(t_vm *v, t_list *process)
{
	int shift;

	if (CARRY == 1)
	{
		shift = reverse_bytes(&ARENA(PC + 1), 2);
		shift %= IDX_MOD;
		if (v->display_mode == 1)
		{
			printf("PC before : %d\t", PC);
			printf("Decale toi de : %d\t", shift);
		}
		PC = (unsigned int)(PC + shift) % MEM_SIZE;
		if (v->display_mode == 1)
			printf("PC after : %d\n", PC);
	}
	else
		PC += 3;
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
