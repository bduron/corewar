/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:32:40 by cpoulet           #+#    #+#             */
/*   Updated: 2017/04/03 18:25:31 by cpoulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_add(t_vm *v, t_list *process)
{
	int		val;
	char	nb_arg;

	nb_arg = 3;
	if (check_arg(3, B_OCT, nb_arg))
	{
		if (ARENA(PC + 2) >= 1 && ARENA(PC + 2) <= 16 &&
			ARENA(PC + 3) >= 1 && ARENA(PC + 3) <= 16 &&
			ARENA(PC + 4) >= 1 && ARENA(PC + 4) <= 16)
		{
			val = REG[ARENA(PC + 2) - 1] + REG[ARENA(PC + 3) - 1];
			printf("val = %d\n", val);
			CARRY = val ? 0 : 1;
			REG[ARENA(PC + 4) - 1] = val;
		}
	}
	octal_shift(process, B_OCT, 4, nb_arg);
}

void	op_sub(t_vm *v, t_list *process)
{
	int		val;
	char	nb_arg;

	nb_arg = 3;
	if (check_arg(4, B_OCT, nb_arg))
	{
		if (ARENA(PC + 2) >= 1 && ARENA(PC + 2) <= 16 &&
			ARENA(PC + 3) >= 1 && ARENA(PC + 3) <= 16 &&
			ARENA(PC + 4) >= 1 && ARENA(PC + 4) <= 16)
		{
			val = REG[ARENA(PC + 2) - 1] - REG[ARENA(PC + 3) - 1];
			printf("val = %d\n", val);
			CARRY = val ? 0 : 1;
			REG[ARENA(PC + 4) - 1] = val;
		}
	}
	octal_shift(process, B_OCT, 4, nb_arg);
}

void	op_and(t_vm *v, t_list *process)
{
	char	nb_arg;

	nb_arg = 3;
	if (check_arg(5, B_OCT, nb_arg))
	{
		(void)v;
	}
	octal_shift(process, B_OCT, 4, nb_arg);
}

void	op_or(t_vm *v, t_list *process)
{
	(void)v;
	(void)process;
}

void	op_xor(t_vm *v, t_list *process)
{
	(void)v;
	(void)process;
}
