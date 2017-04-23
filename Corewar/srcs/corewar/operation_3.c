/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <bduron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:54:01 by bduron            #+#    #+#             */
/*   Updated: 2017/04/23 15:25:24 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_zjmp(t_vm *v, t_list *process)
{
	int shift;

	shift = reverse_bytes(v, PC + 1, 2);
	if (v->display_mode == 1)
	{
	ft_printf("P %4d | zjmp %d ", NPRO, shift);
		if (CARRY)
		ft_printf("OK\n");
		else
		{
		ft_printf("FAILED\n");
			print_adv(v, process, 3);
		}
	}
	shift %= IDX_MOD;
	PC = CARRY == 1 ? (unsigned int)(PC + shift) % MEM_SIZE :
					(PC + 3) % MEM_SIZE;
}

void	op_fork(t_vm *v, t_list *process)
{
	int shift;

	shift = reverse_bytes(v, PC + 1, 2);
	shift %= IDX_MOD;
	if (v->display_mode == 1)
	{
	ft_printf("P %4d | fork %d (%d)\n",
			NPRO, shift, PC + shift);
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
	ft_printf("P %4d | lfork %d (%d)\n",
			NPRO, shift, PC + shift);
		print_adv(v, process, 3);
	}
	add_process(v, process, (unsigned int)(PC + shift) % MEM_SIZE);
	PC += 3;
	PC %= MEM_SIZE;
}
