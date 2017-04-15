/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:33:45 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/15 14:20:46 by cpoulet          ###   ########.fr       */
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
		printf("PC before : %d\t", PC);
		printf("Decale toi de : %d\t", shift);
		PC = (unsigned int)(PC + shift) % MEM_SIZE;
		printf("PC after : %d\n", PC);
		print_arena(v); //DEBUG
	}
	else
	{
		printf("CARRY == 0\n");
		printf("PC before : %d\t", PC);
		PC += 3;
		printf("PC after : %d\n", PC);
	}
}

void	op_fork(t_vm *v, t_list *process)
{
	int shift;

	shift = reverse_bytes(&ARENA(PC + 1), 2);
	shift %= IDX_MOD;
	printf("PC PARENT : %d\t", PC);
	add_process(v, process, (unsigned int)(PC + shift) % MEM_SIZE);
	PC += 3;
	PC %= MEM_SIZE;
	printf("PC ENFANT : %d\n", (unsigned int)(PC + shift) % MEM_SIZE);
	print_arena(v); //DEBUG
}

void	op_lfork(t_vm *v, t_list *process)
{
	int shift;

	shift = reverse_bytes(&ARENA(PC + 1), 2);
	printf("PC PARENT : %d\t", PC);
	add_process(v, process, (unsigned int)(PC + shift) % MEM_SIZE);
	PC += 3;
	PC %= MEM_SIZE;
	printf("PC ENFANT : %d\n", (unsigned int)(PC + shift) % MEM_SIZE);
	print_arena(v); //DEBUG
}
