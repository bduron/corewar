/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 13:55:14 by cpoulet           #+#    #+#             */
/*   Updated: 2017/03/28 17:14:59 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	execute_op(t_vm *v, t_list *process)
{
	printf("EXECUTION : %s\n", op_tab[NEXT_OP].name);
	op_tab[NEXT_OP].f(v, process);
}

void	init_next_op(t_vm *v, t_list *process)
{
	if (ARENA[PC] > 16)
	{
		PC++;
		printf("FAIL !\n");
	}
	else
	{
		NEXT_OP = ARENA[PC] - 1;
		OP_CAST = op_tab[NEXT_OP].cycle - 1; // arbitraire pour le moment
		printf("numero d'op : %2x\t", ARENA[PC]);
		printf("cast moi ce spell noob : %2d\n", OP_CAST);
	}
}

void	operate_process(t_vm *v, t_list *process)
{
	if (NEXT_OP)
		execute_op(v, process);
	init_next_op(v, process);
}
