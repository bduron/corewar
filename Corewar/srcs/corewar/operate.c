/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 13:55:14 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/03 18:25:11 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int reverse_bytes(unsigned char *addr, int nbytes)
{
	unsigned char two_bytes[2];
	unsigned char four_bytes[4];
	
	if (nbytes == 2)
	{
		two_bytes[0] = *(unsigned char *)(addr + 1);
		two_bytes[1] = *(unsigned char *)(addr);
		return (*(short *)&two_bytes[0]);
	}
	if (nbytes == 4)
	{
		four_bytes[0] = *(unsigned char *)(addr + 3);
		four_bytes[1] = *(unsigned char *)(addr + 2);
		four_bytes[2] = *(unsigned char *)(addr + 1);
		four_bytes[3] = *(unsigned char *)(addr);
		return (*(int *)&four_bytes[0]);
	}
	return (-1);
}

void	execute_op(t_vm *v, t_list *process)
{
	printf("EXECUTION : %s\n", op_tab[NEXT_OP].name);
	op_tab[NEXT_OP].f(v, process);
}

void	init_next_op(t_vm *v, t_list *process)
{
	if (ARENA(PC) > 16 || !ARENA(PC))
	{
		NEXT_OP = 0;
		PC++;
		printf("FAIL !\n");
	}
	else
	{
		NEXT_OP = ARENA(PC) - 1;
		OP_CAST = op_tab[NEXT_OP].cycle - 1; // arbitraire pour le moment
		printf("numero d'op : %2x\t", ARENA(PC));
		printf("cast moi ce spell noob : %2d\n", OP_CAST);
	}
}

void	operate_process(t_vm *v, t_list *process)
{
	if (NEXT_OP)
		execute_op(v, process);
	init_next_op(v, process);
}
